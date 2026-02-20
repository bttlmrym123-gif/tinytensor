#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

// 1. Veri Tipleri
typedef enum { TYPE_F32, TYPE_F16, TYPE_I8 } TensorType;

// 2. Esnek Tensör Yapýsý
typedef struct {
    TensorType type;
    int length;        // size_t yerine daha garanti olan int kullandým
    float scale;
    int8_t zero_point;
    
    union {
        float* f32_ptr;
        uint16_t* f16_ptr;
        int8_t* i8_ptr;
    } data;
} TinyTensor;

// 3. Quantization Fonksiyonu
void quantize(TinyTensor* t, float* raw_data) {
    int i; // Eski derleyiciler için deðiþkeni dýþarýda tanýmladým
    for (i = 0; i < t->length; i++) {
        // Formül: Q = (R / S) + Z
        float quantized_val = (raw_data[i] / t->scale) + (float)t->zero_point;
        
        // Sýnýrlandýrma
        if (quantized_val > 127.0f) quantized_val = 127.0f;
        if (quantized_val < -128.0f) quantized_val = -128.0f;
        
        t->data.i8_ptr[i] = (int8_t)quantized_val;
    }
}

int main() {
    float sensor_verileri[] = {0.85f, -0.42f, 0.12f, 0.99f, -0.95f};
    int n = 5;
    int i;

    // Tensör belleði ayýrma
    TinyTensor my_tensor;
    my_tensor.type = TYPE_I8;
    my_tensor.length = n;
    my_tensor.scale = 0.01f;
    my_tensor.zero_point = 0;
    
    // Bellek ayýrma ve tip dönüþümü (C++ uyumu için cast eklendi)
    my_tensor.data.i8_ptr = (int8_t*)malloc(n * sizeof(int8_t));

    if (my_tensor.data.i8_ptr == NULL) {
        printf("Bellek ayirma hatasi!\n");
        return 1;
    }

    quantize(&my_tensor, sensor_verileri);

    printf("--- TinyML Tensor Demosu ---\n");
    for(i = 0; i < n; i++) {
        printf("Float: %.2f -> Int8: %d\n", sensor_verileri[i], my_tensor.data.i8_ptr[i]);
    }

    free(my_tensor.data.i8_ptr);
    return 0;
}
