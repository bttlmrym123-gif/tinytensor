#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

// Desteklenen veri tipleri
typedef enum {
    TYPE_FLOAT32,
    TYPE_INT8
} TensorType;

// Primitive TinyTensor yapısı
typedef struct {
    TensorType type;
    int size;
    union {
        float* f_data;
        int8_t* i8_data;
    } data;
} TinyTensor;

// Float -> int8 Quantization fonksiyonu
int8_t quantize(float value, float scale, int zero_point) {
    int32_t q = (int32_t)((value / scale) + zero_point);

    if (q > 127) q = 127;
    if (q < -128) q = -128;

    return (int8_t)q;
}

// Tensör ortalama hesaplama
float calculate_mean(TinyTensor* t) {
    float sum = 0.0f;

    for (int i = 0; i < t->size; i++) {
        sum += t->data.f_data[i];
    }

    return sum / t->size;
}

int main() {

    printf("=== IoT Sicaklik Sensoru Veri Simulasyonu ===\n\n");

    int size = 5;

    // Float tensör oluştur
    TinyTensor sensorTensor;
    sensorTensor.type = TYPE_FLOAT32;
    sensorTensor.size = size;
    sensorTensor.data.f_data = (float*)malloc(size * sizeof(float));

    // Sensör verileri (örnek)
    float sensorValues[5] = {23.5, 24.1, 22.8, 25.0, 23.9};

    for (int i = 0; i < size; i++) {
        sensorTensor.data.f_data[i] = sensorValues[i];
    }

    printf("Float Sensor Verileri:\n");
    for (int i = 0; i < size; i++) {
        printf("%.2f ", sensorTensor.data.f_data[i]);
    }

    float mean = calculate_mean(&sensorTensor);
    printf("\n\nOrtalama Sicaklik: %.2f\n\n", mean);

    // Quantization parametreleri
    float scale = 0.1f;
    int zero_point = 0;

    // Int8 tensör oluştur
    TinyTensor quantTensor;
    quantTensor.type = TYPE_INT8;
    quantTensor.size = size;
    quantTensor.data.i8_data = (int8_t*)malloc(size * sizeof(int8_t));

    for (int i = 0; i < size; i++) {
        quantTensor.data.i8_data[i] = quantize(sensorTensor.data.f_data[i], scale, zero_point);
    }

    printf("Quantized Int8 Verileri:\n");
    for (int i = 0; i < size; i++) {
        printf("%d ", quantTensor.data.i8_data[i]);
    }

    free(sensorTensor.data.f_data);
    free(quantTensor.data.i8_data);

    return 0;
}
