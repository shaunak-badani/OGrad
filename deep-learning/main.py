from scripts.make_dataset import DatasetFetcher
from scripts.model import ModelHelper, VGGNet


def main():
    dataFetcher = DatasetFetcher()
    imageloader = dataFetcher.getImageTrainloader(subset = True)
    criterion = ModelHelper.getCriterion()
    vgg = VGGNet()
    optimizer = ModelHelper.getOptimizer(vgg)
    num_iters = 2
    device = ModelHelper.getDevice()
    print(" device = ", device)
    ModelHelper.trainModel(vgg, criterion, optimizer, imageloader, num_iters, device)
    print("Done training model")


if __name__ == "__main__":
    main()