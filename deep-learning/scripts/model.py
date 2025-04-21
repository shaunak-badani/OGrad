import torch.nn as nn
import torch.nn.functional as F
import torch
import torch.optim as optim

class CustomCrossEntropyLoss(nn.Module):
    def __init__(self):
        super().__init__()

    def forward(self, output, target):
        N, C = output.shape
        assert (target < C).all(), "label target out of shape!"
        one_hot_labels = F.one_hot(target, num_classes=C)
        assert one_hot_labels.shape == output.shape, "one hot shape is not the same as output!"
        softmaxed_outputs = F.softmax(output, dim = 1)
        loss_value = torch.sum(-one_hot_labels * torch.log(softmaxed_outputs)) / N
        return loss_value

class ModelHelper:

    @classmethod
    def getDevice(cls):
        return "cuda" if torch.cuda.is_available() else "cpu"

    @classmethod
    def getOptimizer(cls, model):
        return optim.AdamW(model.parameters(), lr = 1e-3)
    
    @classmethod
    def getCriterion(cls):
        return CustomCrossEntropyLoss()
    
    @classmethod
    def trainModel(cls, model, criterion, optimizer, trainloader, num_iter, device):
        model = model.to(device)
        model.train() # Set the model to training mode
        cost = []
        for epoch in range(num_iter):
            running_loss = 0.0
            for i, data in enumerate(trainloader):
                # Get the inputs X and labels y for the minibatch
                inputs, labels = data[0].to(device), data[1].to(device)
                # Zero the gradients of the weights each iteration
                optimizer.zero_grad()
                # Calculate the predictions and the cost/loss
                outputs = model(inputs)
                loss = criterion(outputs, labels)
                # Use autograd to calculate the gradient of the cost with respect to each weight
                loss.backward()
                # Use the optimizer to do the weights update
                optimizer.step()
                # Add the loss to running loss for the epoch
                running_loss += loss.item()
            cost.append(running_loss)
        return cost


class VGGNet(nn.Module):
    def __init__(self):
        super().__init__()
        in_channels = 3
        self.conv1 = nn.ModuleList([
            nn.Conv2d(in_channels, 64, 3, padding="same"),
            nn.ReLU(),
            nn.Conv2d(64, 64, 3, padding ="same"),
            nn.ReLU(),
            nn.MaxPool2d(2, 2)
        ])
        self.conv2 = nn.ModuleList([
            nn.Conv2d(64, 128, 3, padding = "same"),
            nn.ReLU(),
            nn.Conv2d(128, 128, 3, padding = "same"),
            nn.ReLU(),
            nn.MaxPool2d(2, 2)
        ])
        self.conv3 = nn.ModuleList([
            nn.Conv2d(128, 256, 3, padding = "same"),
            nn.ReLU(),
            nn.Conv2d(256, 256, 3, padding = "same"),
            nn.ReLU(),
            nn.Conv2d(256, 256, 3, padding = "same"),
            nn.ReLU(),
            nn.Conv2d(256, 256, 3, padding = "same"),
            nn.ReLU(),
            nn.MaxPool2d(2, 2)
        ])
        self.conv4 = nn.ModuleList([
            nn.Conv2d(256, 512, 3, padding = "same"),
            nn.ReLU(),
            nn.Conv2d(512, 512, 3, padding = "same"),
            nn.ReLU(),
            nn.Conv2d(512, 512, 3, padding = "same"),
            nn.ReLU(),
            nn.Conv2d(512, 512, 3, padding = "same"),
            nn.ReLU(),
            nn.MaxPool2d(2, 2)
        ])

        self.conv5 = nn.ModuleList([
            nn.Conv2d(512, 512, 3, padding = "same"),
            nn.ReLU(),
            nn.Conv2d(512, 512, 3, padding = "same"),
            nn.ReLU(),
            nn.Conv2d(512, 512, 3, padding = "same"),
            nn.ReLU(),
            nn.Conv2d(512, 512, 3, padding = "same"),
            nn.ReLU(),
            nn.MaxPool2d(2, 2)
        ])
        self.flatten = nn.Flatten()
        self.linears = nn.ModuleList([
            nn.Linear(2048, 4096),
            nn.ReLU(),
            nn.Linear(4096, 4096),
            nn.ReLU(),
            nn.Linear(4096, 200)
        ])

    def forward(self, x):
        for layer in self.conv1:
            x = layer(x)
        for layer in self.conv2:
            x = layer(x)
        for layer in self.conv3:
            x = layer(x)
        for layer in self.conv4:
            x = layer(x)
        for layer in self.conv5:
            x = layer(x)
        x = self.flatten(x)

        for linear in self.linears:
            x = linear(x)
        return x
    
if __name__ == "__main__":
    vgg = VGGNet()