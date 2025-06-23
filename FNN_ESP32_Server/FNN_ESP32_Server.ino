#include <WiFi.h>
#include <ArduinoJson.h>
#include <aifes.h>

#include "FNN_utility.h"
#include "WiFi_utility.h"
#include "json_utility.h"

String weights = "0";

void setup() {
  Serial.begin(115200);
  setup_WiFi_server();
  train_fnn();

  delay(500);
}
void loop() {
  delay(10000);
  train_fnn();
}
void train_fnn() {
  Serial.println("\n\nStart training: ");

  AIFES_E_activations FNN_activations[FNN_LAYERS - 1];
  FNN_activations[0] = AIfES_E_relu;     //AIfES_E_relu activation for first hidden (dense) layer
  FNN_activations[1] = AIfES_E_relu;     //AIfES_E_relu activation for second hidden (dense) layer
  FNN_activations[2] = AIfES_E_sigmoid;  //AIfES_E_sigmoid activation for output (dense) layer

  uint16_t weight_number = AIFES_E_flat_weights_number_fnn_f32(FNN_structure, FNN_LAYERS);
  Serial.print(F("Weights: "));
  Serial.println(weight_number);
  float FlatWeights[weight_number];


  AIFES_E_model_parameter_fnn_f32 FNN;
  FNN.layer_count = FNN_LAYERS;
  FNN.fnn_structure = FNN_structure;
  FNN.fnn_activations = FNN_activations;
  FNN.flat_weights = FlatWeights;

  AIFES_E_init_weights_parameter_fnn_f32 FNN_INIT_WEIGHTS;

  if(weights.equals("0")){
    Serial.println("\nWeights not present");
    FNN_INIT_WEIGHTS.init_weights_method = AIfES_E_init_glorot_uniform;
  }
  else{
    Serial.println("\nWeights already present");
    Serial.print(weights);
    deserializeJsonToFloat(weight_number, FlatWeights, weights);
    FNN_INIT_WEIGHTS.init_weights_method = AIfES_E_init_no_init; //No weight init. Starting weights are already available or if you want to continue training
    weights = "0";
  }

  AIFES_E_training_parameter_fnn_f32 FNN_TRAIN;
  FNN_TRAIN.optimizer = AIfES_E_adam;
  FNN_TRAIN.loss = AIfES_E_crossentropy;

  FNN_TRAIN.learn_rate = 0.001;
  FNN_TRAIN.sgd_momentum = 0.0;  //Not using sgd
  FNN_TRAIN.batch_size = 64;
  FNN_TRAIN.epochs = 500;
  FNN_TRAIN.epochs_loss_print_interval = 100;

  FNN_TRAIN.loss_print_function = printLoss;
  FNN_TRAIN.early_stopping = AIfES_E_early_stopping_on;
  FNN_TRAIN.early_stopping_target_loss = 0.05;

  int8_t error = 0;  //Error Handling

  // -------------------------------- do the training ----------------------------------
  // In the training function, the FNN is set up, the weights are initialized and the training is performed.
  output_shape[0] = DATASETS;
  output_tensor = AITENSOR_2D_F32(output_shape, output_data);
  error = AIFES_E_training_fnn_f32(&input_tensor, &target_tensor, &FNN, &FNN_TRAIN, &FNN_INIT_WEIGHTS, &output_tensor);
  error_handling_training(error);
  Serial.println("Training end");

  // -------------------------------- do the inference ----------------------------------

  //Inference on test data
  output_shape[0] = TEST_DATASET;
  output_tensor = AITENSOR_2D_F32(output_shape, output_data);
  error = AIFES_E_inference_fnn_f32(&test_input_tensor, &FNN, &output_tensor);
  error_handling_inference(error);
  printResult_testData(testY, output_data);

  //Inference on train data
  output_shape[0] = DATASETS;
  output_tensor = AITENSOR_2D_F32(output_shape, output_data);
  error = AIFES_E_inference_fnn_f32(&input_tensor, &FNN, &output_tensor);
  error_handling_inference(error);
  printResult_trainingData(trainY, output_data);

  
  while (weights.equals("0") || weights.isEmpty())
  {
    Serial.println("Wait Client");
    weights = syncWeights_server(weight_number, FlatWeights);
  }
  
  weights = deserializeJsonToFloat(weight_number, FlatWeights, weights);
  Serial.print("\nCode ended on server");

}