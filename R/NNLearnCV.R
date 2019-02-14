NNLearnCV <- function(X.mat, y.vec, max.neighbors=30,
                            fold.vec=NULL, n.folds=5) 
{

  #if fold.vec is null randomly assign folds
  if(fold.vec == null)
  {
    fold.vec <- sample(rep(1:n.folds, l=nrow(X.mat)))
  }

  # make sure that fold.vec is the same size as y.vec
  # which is the same as the number of rows in X.mat
  if(nrow(X.mat) != length(y.vec) &&  
     nrow(X.mat) != length(fold.vec) &&
     length(fold.vec) != length(y.vec))
  {
    stop("y.vec, fold.vec, and X.mat columns are not equal.
         Program could not complete.")
  }
  
  # perform cross-validation to compute two matrices 
  # of mean loss values
  
  # If the labels (y.vec) are all in {0,1} then the 
  # loss function should be the 01-loss (binary 
  # classification), otherwise use the square loss (regression).
  
  # run NN1toKmaxPredict to compute predictions, 
  # then a matrix of loss values then use colMeans() 
  # and store the result in one column of 
  # train.loss.mat/validation.loss.mat.
  for(fold.i in seq_along(unique.folds)){
    for(prediction.set.name in c("train", "validation")){
      pred.mat <- NN1toKmaxPredict(
        train.features, train.labels,
        prediction.set.features, max.neighbors)
      loss.mat <- if(labels.all.01){
        ifelse(pred.mat>0.5, 1, 0) != y.vec #zero-one loss for binary classification.
      }else{
        (pred.mat-y.vec)^2 #square loss for regression.
      }
      train.or.validation.loss.mat[, fold.i] <- colMeans(loss.mat)
    }
  }
  
  # return a list with the following named elements:
  # X.mat, y.vec: training data.
  # train.loss.mat, validation.loss.mat (matrices of loss values for each fold and number of neighbors).
  # train.loss.vec, validation.loss.vec (vectors with max.neighbors elements: mean loss over all folds).
  # selected.neighbors (number of neighbors selected by minimizing the mean validation loss).
  # predict(testX.mat), a function that takes a matrix of inputs/features and returns a vector of predictions.
  returnList <- list("X.mat" = X.mat, "y.vec" = y.vec, "train.loss.mat" = train.loss.mat,
                 "validation.loss.mat" = validation.loss.mat, "train.loss.vec" = train.loss.vec, 
                 "validation.loss.vec" = validation.loss.vec, "selected.neighbors" = selected.neighbors, 
                 "predict(testX.mat)" = predict(testX.mat))
  
}
