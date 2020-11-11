import cv2
import time
from pysimplendi import NDIReceiver

if __name__ == '__main__':
    # initialize NDIReceiver
    receiver = NDIReceiver()

    # get NDI source list
    source_list = receiver.getSourceList()
    for s in source_list:
        print(s)

    # exit if no NDI sources
    if len(source_list) == 0:
        exit(0)

    # set source
    receiver.setSource(source_list[0])

    window_name = 'frame'
    counter = 0

    while True:
        # get current frame
        frame = receiver.getCurrentFrame()

        if len(frame) >= 3:
            counter += 1
            cv2.imshow(window_name, frame)

            if cv2.waitKey(1) & 0xFF == ord('q'):
                break
        time.sleep(0.1)

    cv2.destroyWindow(window_name)
