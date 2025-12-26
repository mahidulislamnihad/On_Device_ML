#include "inference.h"

// Tensor arena
uint8_t tensor_arena[kTensorArenaSize];

// Global objects
const tflite::Model* model;  
tflite::MicroInterpreter* interpreter;
tflite::AllOpsResolver resolver;

// Codition labels
const char* labels[13] = {
    "UNDEFINED", "HOT_DRY", "HOT_HUMID", "WARM_HUMID", "WARM",
    "HUMID_UNCOMFORTABLE", "COMFORTABLE", "DRY_MILD", "COOL_DAMP",
    "COOL", "COLD_DAMP", "COLD", "VERY_COLD"
};

void setupModel() {
    model = tflite::GetModel(env_classifier_int8_tflite);
    if (model->version() != TFLITE_SCHEMA_VERSION) {
        Serial.println("Model schema version mismatch!");
        while(1);
    }

    static tflite::MicroInterpreter static_interpreter(
        model,
        resolver,
        tensor_arena,
        kTensorArenaSize
    );

    interpreter = &static_interpreter;

    TfLiteStatus allocate_status = interpreter->AllocateTensors();
    if (allocate_status != kTfLiteOk) {
        Serial.println("AllocateTensors() failed");
        while(1);
    }
}

const char* runInference(float temperature, float humidity) {
    TfLiteTensor* input = interpreter->input(0);

    // tensor input (shape [1,4]: temperature, humidity, delta_t, delta_h)
    input->data.f[0] = temperature;
    input->data.f[1] = humidity;
    input->data.f[2] = 0.0f; // delta_t
    input->data.f[3] = 0.0f; // delta_h

    if (interpreter->Invoke() != kTfLiteOk) {
        Serial.println("Invoke failed!");
        return "ERROR";
    }

    TfLiteTensor* output = interpreter->output(0);

    // predicting class using maxindex
    int maxIndex = 0;
    float maxVal = output->data.f[0];
    for (int i = 1; i < 13; i++) {  
        if (output->data.f[i] > maxVal) {
            maxVal = output->data.f[i];
            maxIndex = i;
        }
    }

    return labels[maxIndex];
}
