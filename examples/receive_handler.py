import time
from pysimplendi import NDIReceiver


def handler(image):
    print(image.shape)


if __name__ == '__main__':
    # initialize NDIReceiver
    receiver = NDIReceiver()
    # get NDI source list
    source_list = receiver.getSourceList()

    for s in source_list:
        print(s)

    if len(source_list) == 0:
        exit(0)

    # set source (return value -> true:Success, false:Failed)
    print(receiver.setSource(source_list[0]))

    receiver.addHandler("test", handler)

    window_name = 'frame'

    time.sleep(20)
