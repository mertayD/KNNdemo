int knn(
    const double *train_inputs_ptr,//n_observations, n_features
    const double *train_label_ptr, //n_observations
    const double *test_input_ptr,
    const int n_observations, const int n_features, const int max_neighbours,
    double *test_predictions_ptr //mac_neighbors
);