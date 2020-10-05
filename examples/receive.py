import cv2
import numpy as np
import time
from pysimplendi import NDIReceiver

if __name__ == '__main__':
    receiver = NDIReceiver()
    source_list = receiver.getSourceList()

    for s in source_list:
        print(s)

    if len(source_list) == 0:
        exit(0)

    print(len(source_list))

    print(receiver.setSource(source_list[0]))

    window_name = 'frame'
    counter = 0

    while True:
        frame = receiver.getCurrentFrame()
        # print(frame.shape)
        if len(frame) >= 3:
            # cv2.imwrite('output/' + str(counter) + '.png', frame)
            counter += 1
            # display = np.copy(frame)
            cv2.imshow(window_name, frame)

            if frame.shape[2] == 4:
                r, g, b, a = cv2.split(frame)
                s = np.sum(r)
                print("sum", s)

            if cv2.waitKey(1) & 0xFF == ord('q'):
                break
        time.sleep(0.1)
    cv2.destroyWindow(window_name)
