import cv2
import numpy as np
from pysimplendi import NDISender

if __name__ == "__main__":
    sender = NDISender("hello")
    image = cv2.imread("examples/img/test-trans.png", cv2.IMREAD_UNCHANGED)
    image2 = cv2.imread("examples/img/test.png")

    i = 0

    print(image2.shape)
    while True:
        i = (i + 1) % 30
        print(i)
        if i > 15:
            sender.send(image)
        else:
            sender.send(image2)

