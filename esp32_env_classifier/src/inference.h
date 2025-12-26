#ifndef INFERENCE_H
#define INFERENCE_H

#include <Arduino.h>
#include "model_data.h"
#include "tensorflow/lite/micro/micro_interpreter.h"
#include "tensorflow/lite/micro/all_ops_resolver.h"
#include "tensorflow/lite/schema/schema_generated.h"

// Tensor arena size 
constexpr int kTensorArenaSize = 8 * 1024;
extern uint8_t tensor_arena[kTensorArenaSize];

// Functions
void setupModel();
const char* runInference(float temperature, float humidity);

#endif
