# pySimpleNDI

pySimpleNDI is a library that that makes it easy to use NDI in Python.

## requirements
#### Cmake
https://cmake.org/download/

### NDI SDK
download from https://ndi.tv/sdk/
#### MacOS & Windows
only run installer.

#### linux
1. extract downloaded file.
1. run `InstallNDISDK_v4_Linux.sh` in the extracted folder.
1. create symlink to `/NDI SDK for Linux/libndi.so.4` in `/usr/lib`.

## Install
type `pip install pysimplendi`.

## Example

### NDISender

NDISender can send np array([width, height, 3] or [width, height, 4])


```python
import cv2
from pysimplendi import NDISender

# initialize sender
sender = NDISender("pysimplendi")
# transparent image [width, height, 4]
image = cv2.imread("examples/img/test-trans.png", cv2.IMREAD_UNCHANGED)
# normal image [width, height, 3]
image2 = cv2.imread("examples/img/test.png")

sender.send(image)
sender.send(image2)
```

### NDIReceiver
NDISender can receive np array([width, height, 3] or [width, height, 4])

```python
import cv2
from pysimplendi import NDIReceiver

receiver = NDIReceiver()
source_list = receiver.getSourceList()


# 1. get current frame
frame = receiver.getCurrentFrame()

# or

# 2. add handler
# call when frame received
def handler(image):
    print(image.shape)

receiver.addHandler("test", handler)

```

