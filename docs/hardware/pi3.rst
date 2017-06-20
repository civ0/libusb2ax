Raspberry Pi 3
==============

Because the USB ports of the Raspberry Pi 3 aren't the best, the USB2AX does not work out of the
box. Because of that, some kernel parameters must be set at boot. This is done by editing the file
``/boot/cmdline.txt``.

By default it looks like this::

  dwc_otg.lpm_enable=0 console=serial0,115200 console=tty1 root=/dev/mmcblk0p7 rootfstype=ext4 elevator=deadline fsck.repair=yes rootwait

After adding ::

  dwc_otg.fiq_enable=1 dwc_otg.fiq_fsm_enable=1 dwc_otg.fiq_fsm_mask=0x3 dwc_otg.speed=1 

to the file before ``console=serial0,115200`` it should look like this::

  dwc_otg.lpm_enable=0 dwc_otg.fiq_enable=1 dwc_otg.fiq_fsm_enable=1 dwc_otg.fiq_fsm_mask=0x3 dwc_otg.speed=1 console=serial0,115200 console=tty1 root=/dev/mmcblk0p7 rootfstype=ext4 elevator=deadline fsck.repair=yes rootwait

Caution
^^^^^^^

These changes prevent USB keyboards from working and possibly other devices. Make sure you can
access the Pi using SSH, before applying these changes.

If you have added some other parameters, this might interfere.