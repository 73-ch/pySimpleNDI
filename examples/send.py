import cv2
from pysimplendi import NDISender

if __name__ == "__main__":
    sender = NDISender("pysimplendi")
    # transparent image [width, height, 4]
    transparent = cv2.imread("examples/img/test-trans.png", cv2.IMREAD_UNCHANGED)
    # normal image [width, height, 3]
    normal = cv2.imread("examples/img/test.png")

    i = 0

    while True:
        i = (i + 1) % 30
        print(i)
        if i > 15:
            # send transparent image
            sender.send(transparent)
        else:
            # send image
            sender.send(normal)
