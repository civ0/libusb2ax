udev rule
=========

To access the USB2AX without superuser rights, a udev rule is needed. The rule is supplied in the
file ``usb2ax.rules`` with the following content::

  KERNEL=="ttyACM[0-9]", ATTRS{idVendor}=="16d0", ATTRS{idProduct}=="06a7", SYMLINK="usb2ax%n", MODE="0660"

Copy this file to ``/etc/udev/rules.d/`` and execute the following command as superuser::

  udevadm control --reload

After that, the USB2AX can be accessed via the symlink under ``/dev/usb2axn`` as normal user.