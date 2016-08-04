// From linux-2.6.33.3/drivers/usb/musb/musb_core.c#L1906

static int
_init_controller(struct device *dev, int nIrq, void *ctrl)
{
  switch (plat->mode) {
  case MUSB_HOST:
#ifdef CONFIG_USB_MUSB_HDRC_HCD
    break;
#else
    goto bad_config;
#endif
  case MUSB_PERIPHERAL:
#ifdef CONFIG_USB_GADGET_MUSB_HDRC
    break;
#else
    goto bad_config;
#endif
  case MUSB_OTG:
#ifdef CONFIG_USB_MUSB_OTG
    break;
#else
  bad_config:
#endif
  default:
    dev_err(dev, "incompatible Kconfig role setting\n");
    return -EINVAL;
  }
}
