import time
from pysimplendi import NDIReceiver


def handler():
    print("hello")


if __name__ == '__main__':
    receiver = NDIReceiver()
    source_list = receiver.getSourceList()

    for s in source_list:
        print(s)

    if len(source_list) == 0:
        exit(0)

    # set source
    print(receiver.setSource(source_list[0]))

    receiver.addHandler("test", handler)

    window_name = 'frame'

    time.sleep(20)
