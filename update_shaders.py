import os
import shutil

demos = [
    "AudioExample",
    "Example2D",
    "InterpolationExample"
]

for demo in demos:
    shaderPath = f"./demos/{demo}/assets/shaders/default2D"
    shutil.rmtree(shaderPath, True)
    shutil.copytree("./project_template/assets/shaders/default2D",  shaderPath)