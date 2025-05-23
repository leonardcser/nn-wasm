#include "../core/nn.h"
#include <cstddef>
#include <emscripten.h>

extern "C" {

EMSCRIPTEN_KEEPALIVE
void nn_seed_random_generator(unsigned int seed_val) {
    nn::seed_random_generator(seed_val);
}

EMSCRIPTEN_KEEPALIVE
nn::Model *nn_create_model(int model_input_dim, int num_model_layers,
                           const int *layer_types_arr_int,
                           const int *layer_params_arr_int) {
    // The integer array from JS is cast to nn::LayerType*. This assumes the
    // enum values match. layer_params_arr_int provides parameters like
    // output_neurons for dense layers.
    return nn::create_model(
        model_input_dim, num_model_layers,
        reinterpret_cast<const nn::LayerType *>(layer_types_arr_int),
        layer_params_arr_int);
}

EMSCRIPTEN_KEEPALIVE
void nn_free_model(nn::Model *model) { nn::free_model(model); }

EMSCRIPTEN_KEEPALIVE
void nn_initialize_weights_xavier_uniform(nn::Model *model) {
    nn::initialize_weights_xavier_uniform(model);
}

EMSCRIPTEN_KEEPALIVE
void nn_initialize_weights_he_uniform(nn::Model *model) {
    nn::initialize_weights_he_uniform(model);
}

EMSCRIPTEN_KEEPALIVE
void nn_initialize_weights_uniform_range(nn::Model *model, float min_val,
                                         float max_val) {
    nn::initialize_weights_uniform_range(model, min_val, max_val);
}

EMSCRIPTEN_KEEPALIVE
void nn_initialize_biases_zero(nn::Model *model) {
    nn::initialize_biases_zero(model);
}

EMSCRIPTEN_KEEPALIVE
nn::Dataset *nn_create_dataset(int num_samples, int input_dim, int output_dim,
                               const float *inputs_flat_data,
                               const float *targets_flat_data) {
    return nn::create_dataset(num_samples, input_dim, output_dim,
                              inputs_flat_data, targets_flat_data);
}

EMSCRIPTEN_KEEPALIVE
void nn_free_dataset(nn::Dataset *dataset) { nn::free_dataset(dataset); }

EMSCRIPTEN_KEEPALIVE
void nn_train_model(nn::Model *model, const nn::Dataset *train_data,
                    nn::TrainConfig *config,
                    const nn::Dataset *validation_data) {
    nn::train_model(model, train_data, config, validation_data);
}

EMSCRIPTEN_KEEPALIVE
float nn_step_model(nn::Model *model,
                    const float *batch_inputs,  // float*
                    const float *batch_targets, // float*
                    int num_samples_in_batch, const nn::TrainConfig *config) {
    return nn::step_model(model, batch_inputs, batch_targets,
                          num_samples_in_batch, config);
}

EMSCRIPTEN_KEEPALIVE
const float *nn_get_model_output(const nn::Model *model) {
    return nn::get_model_output(model);
}

EMSCRIPTEN_KEEPALIVE
const float *nn_predict(nn::Model *model, const float *input_sample) {
    return nn::predict(model, input_sample);
}

EMSCRIPTEN_KEEPALIVE
const float *nn_get_layer_output_activations(const nn::Model *model,
                                             int layer_index,
                                             int *out_activation_size) {
    return nn::get_layer_output_activations(model, layer_index, out_activation_size);
}

} // extern "C"
