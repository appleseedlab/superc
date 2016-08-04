// From linux-2.6.29.6/include/linux/kernel.h
#define KERN_ERR        "<3>"   /* error conditions                     */


// From linux-2.6.29.6/sound/pci/intel8x0.c

// This was introduced in linux-2.6.19 and changed in linux-2.6.30 to
// remove this ugliness.

static int snd_intel8x0_ich_chip_init(struct intel8x0 *chip, int probing)
{
#ifdef CONFIG_SND_AC97_POWER_SAVE
	/* do cold reset - the full ac97 powerdown may leave the controller
	 * in a warm state but actually it cannot communicate with the codec.
	 */
	iputdword(chip, ICHREG(GLOB_CNT), cnt & ~ICH_AC97COLD);
	cnt = igetdword(chip, ICHREG(GLOB_CNT));
	udelay(10);
	iputdword(chip, ICHREG(GLOB_CNT), cnt | ICH_AC97COLD);
	msleep(1);
#else
	/* finish cold or do warm reset */
	cnt |= (cnt & ICH_AC97COLD) == 0 ? ICH_AC97COLD : ICH_AC97WARM;
	iputdword(chip, ICHREG(GLOB_CNT), cnt);
	end_time = (jiffies + (HZ / 4)) + 1;
	do {
		if ((igetdword(chip, ICHREG(GLOB_CNT)) & ICH_AC97WARM) == 0)
			goto __ok;
		schedule_timeout_uninterruptible(1);
	} while (time_after_eq(end_time, jiffies));
	snd_printk(KERN_ERR "AC'97 warm reset still in progress? [0x%x]\n",
		   igetdword(chip, ICHREG(GLOB_CNT)));
	return -EIO;

      __ok:
#endif
after;
}
