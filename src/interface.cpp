#include "knn.h"
#include <R.h>
#include <R_ext/Rdynload.h>
void knn_interface(  const double *train_inputs_ptr,//n_observations, n_features
                     const double *train_label_ptr, //n_observations
                     const double *test_input_ptr,
                     const int *n_observations_ptr, 
                     const int *n_features_ptr, 
                     const int *max_neighbours_ptr,
                     double *test_predictions_ptr //mac_neighbors
){
  int status = knn(train_inputs_ptr, train_label_ptr, test_input_ptr,
                   *n_observations_ptr, *n_features_ptr, *max_neighbours_ptr,
                  test_predictions_ptr);
  
  if(status != 0){
    error("non-zero exit status from knn");
  }
}

R_CMethodDef cMethods[] = {
  {"knn_interface" , (DL_FUNC) &knn_interface, 7},
  {NULL,NULL,0}
};

extern "C" {
  void R_init_nearestNeighborsDemo(DllInfo *info){
    R_registerRoutines(info, cMethods, NULL, NULL, NULL);
    R_useDynamicSymbols(info, FALSE);
  }
}
