/**
 * This module defines the neural network structure, training/test data, tensors,
 * and helper functions to visualize results and handle errors.
 */

#ifndef FNN_UTILITY_H
#define FNN_UTILITY_H

#include <aifes.h>

//----- FNN Constants -----

/**
 * @brief Number of layers in the FNN.
 */
#define FNN_LAYERS 4

/**
 * @brief Number of training samples.
 */
#define DATASETS 1024

/**
 * @brief Number of test samples.
 */
#define TEST_DATASET 126

/**
 * @brief Number of features per sample (input size).
 */
#define FEATURES 15

//----- Utility Functions -----

/**
 * @brief Prints the current loss value during training.
 * @param loss The current loss value to print.
 */
void printLoss(float loss);

/**
 * @brief Handles and prints training-related errors returned by AIfES.
 * @param error_nr The error code returned by the AIfES training function.
 */
void error_handling_training(int8_t error_nr);

/**
 * @brief Handles and prints inference-related errors returned by AIfES.
 * @param error_nr The error code returned by the AIfES inference function.
 */
void error_handling_inference(int8_t error_nr);

/**
 * @brief Prints the expected and predicted values on the test dataset.
 * @param testY Array of true labels from the test dataset.
 * @param output_data Array of predicted values from the FNN.
 */
void printResult_testData(float testY[TEST_DATASET], float output_data[TEST_DATASET]);

/**
 * @brief Prints the expected and predicted values on the training dataset.
 * @param trainY Array of true labels from the training dataset.
 * @param output_data Array of predicted values from the FNN.
 */
void printResult_trainingData(float trainY[DATASETS], float output_data[DATASETS]);

//----- FNN Configuration -----

/**
 * @brief Defines the FNN structure: 15 input neurons, two hidden layers of 16 neurons, and 1 output neuron.
 */
extern uint32_t FNN_structure[FNN_LAYERS];

//----- Training Data -----

/**
 * @brief Training input data (X) with shape [DATASETS][FEATURES].
 */
extern float trainX[DATASETS][FEATURES];

/**
 * @brief Shape of the input tensor for training.
 */
extern uint16_t input_shape[];

/**
 * @brief AIfES input tensor for training.
 */
extern aitensor_t input_tensor;

/**
 * @brief Training target labels (Y).
 */
extern float trainY[DATASETS];

/**
 * @brief Shape of the target tensor.
 */
extern uint16_t target_shape[];

/**
 * @brief AIfES target tensor for training.
 */
extern aitensor_t target_tensor;

//----- Test Data -----

/**
 * @brief Test input data (X) with shape [TEST_DATASET][FEATURES].
 */
extern float testX[TEST_DATASET][FEATURES];

/**
 * @brief Shape of the input tensor for testing.
 */
extern uint16_t test_input_shape[];

/**
 * @brief AIfES input tensor for testing.
 */
extern aitensor_t test_input_tensor;

/**
 * @brief Test target labels (Y).
 */
extern float testY[TEST_DATASET];

/**
 * @brief Shape of the target tensor for testing.
 */
extern int16_t test_target_shape[];

/**
 * @brief AIfES target tensor for testing.
 */
extern aitensor_t test_target_tensor;

//----- Output Tensor -----

/**
 * @brief Array to store output predictions (same size as training set for now).
 */
extern float output_data[DATASETS];

/**
 * @brief Shape of the output tensor.
 */
extern uint16_t output_shape[2];

/**
 * @brief AIfES output tensor used after inference.
 */
extern aitensor_t output_tensor;

#endif // FNN_UTILITY_H
