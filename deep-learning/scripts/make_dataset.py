import os
from torchvision.datasets import ImageFolder
from torch.utils.data import DataLoader, Subset
from torchvision import transforms

class DatasetFetcher:
    """
    Class to fetch the tiny imagenet data
    """

    data_dir = "./data/tiny-imagenet-200"
    train_dir = os.path.join(data_dir, "train")
    val_dir = os.path.join(data_dir, "val")
    

    def getImageTrainloader(self, subset = False):
        """
        Returns image loader for data
        """
        train_transforms = transforms.Compose([
            transforms.ToTensor(),
            transforms.RandomHorizontalFlip(),
            transforms.Normalize(0.5, 0.5)
        ])
        train_dataset = ImageFolder(self.train_dir, transform = train_transforms)
        if subset:
            train_dataset = Subset(train_dataset, list(range(100)))
        return DataLoader(train_dataset, batch_size=4, shuffle=True, num_workers=2)
