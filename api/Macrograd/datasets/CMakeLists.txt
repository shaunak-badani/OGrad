# download mnist datasets:

set(MNIST_TRAIN_URL "https://pjreddie.com/media/files/mnist_train.csv")

message("Downloading MNIST training data")

file(DOWNLOAD ${MNIST_TRAIN_URL} "${CMAKE_SOURCE_DIR}/datasets/mnist/mnist_train.csv"
    SHOW_PROGRESS
    EXPECTED_HASH SHA256=fb60bc58af4dac3554e394af262b3184479833d3cc540ff8783f274b73492d5d
)    

message("Downloading MNIST testing data")

set(MNIST_TEST_URL "https://pjreddie.com/media/files/mnist_test.csv")

file(DOWNLOAD ${MNIST_TRAIN_URL} "${CMAKE_SOURCE_DIR}/datasets/mnist/mnist_test.csv" 
    SHOW_PROGRESS
    EXPECTED_HASH SHA256=fb60bc58af4dac3554e394af262b3184479833d3cc540ff8783f274b73492d5d)
    
# end download