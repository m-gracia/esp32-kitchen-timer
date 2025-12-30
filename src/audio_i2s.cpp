#include <math.h>
#include "my_def.h"
#include "audio_i2s.h"

void setupI2S() {
    // Driver
    i2s_config_t i2s_config = {
        .mode = (i2s_mode_t)(I2S_MODE_MASTER | I2S_MODE_TX),
        .sample_rate = 11025,                            // WAV sr (11025, 22050, 44100, etc)
        .bits_per_sample = I2S_BITS_PER_SAMPLE_16BIT,
        .channel_format = I2S_CHANNEL_FMT_ONLY_LEFT,   // NS4168 on LEFT channel
        .communication_format = I2S_COMM_FORMAT_STAND_MSB, // NOT => I2S_COMM_FORMAT_STAND_I2S
        .intr_alloc_flags = ESP_INTR_FLAG_LEVEL1,
        .dma_buf_count = 8,
        .dma_buf_len = 64,
        .use_apll = false,
        .tx_desc_auto_clear = true
    };
    i2s_driver_install(I2S_NUM, &i2s_config, 0, NULL);

    // Pins
    i2s_pin_config_t pin_config = {
        .bck_io_num = I2S_BCLK,
        .ws_io_num = I2S_LRC,
        .data_out_num = I2S_DOUT,
        .data_in_num = I2S_PIN_NO_CHANGE
    };
    i2s_set_pin(I2S_NUM, &pin_config);
}

void playSound(const uint8_t* data, uint32_t len) {
    size_t bytes_written;
    
    // Skip first 44 bytes WAV header
    i2s_write(I2S_NUM, data + 44, len - 44, &bytes_written, portMAX_DELAY);
}

void playSoundVol(const uint8_t* data, uint32_t len, int volume) {
    size_t bytes_written;
    uint32_t data_len = len - 44; // Skip WAV header
    int16_t* temp_buffer = (int16_t*)malloc(data_len);

    // Reduce volume to avoid distortion
    if (volume <= 15 ) volume = 0;
    else volume -= 15;

    if (temp_buffer) {
        memcpy(temp_buffer, data + 44, data_len);
        // Set volume
        float factor = volume / 100.0f;
        for (size_t i = 0; i < data_len / 2; i++) {
            temp_buffer[i] = (int16_t)(temp_buffer[i] * factor);
        }
        
        i2s_write(I2S_NUM_0, temp_buffer, data_len, &bytes_written, portMAX_DELAY);
        free(temp_buffer);
    }
}

void playTone(float frecuency, float duration, int volume) {
    const int sample_rate = 11025; // Same rate as driver.sample_rate
    size_t bytes_escritos;
    float factorVolumen = volume / 100.0f;
    
    int num_samples = (int)(duration * sample_rate);
    
    const int BUFFER_SIZE = 512;
    int16_t samples[BUFFER_SIZE];

    for (int i = 0; i < num_samples; i += BUFFER_SIZE) {
        int chunk_size = (i + BUFFER_SIZE > num_samples) ? (num_samples - i) : BUFFER_SIZE;
        
        for (int j = 0; j < chunk_size; j++) {
            // Fórmula de la onda senoidal: A * sin(2 * PI * f * t)
            float t = (float)(i + j) / sample_rate;
            float valor = sin(2 * M_PI * frecuency * t);
            
            // Set volume
            samples[j] = (int16_t)(valor * 32760 * factorVolumen);
        }
        i2s_write(I2S_NUM_0, samples, chunk_size * sizeof(int16_t), &bytes_escritos, portMAX_DELAY);
    }
}