import torch


# Generate Concat operator with Float32, Rank-4 and dim 0 (batch)
class net_concat(torch.nn.Module):
    def __init__(self):
        super().__init__()

    def forward(self, inputs):
        return torch.cat((inputs[0], inputs[1]), 0)

    def onnx_opset_version(self):
        # TODO set to appropriate value
        return 14


_model_ = net_concat()

_inputs_ = [torch.randn(1, 32, 1, 8), torch.randn(1, 32, 1, 8)]
