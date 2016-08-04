int main(char **argv, int argc) {

	void issue_volchange(const unsigned int oldvol,
                       const unsigned int newvol)
	{
		unsigned int i = oldvol;

		while (i > newvol) {
      printf("volume up\n");
			i--;
		}
		while (i < newvol) {
      printf("volume down\n");
			i++;
		}
	}

	void issue_brightnesschange(const unsigned int oldbrt,
                              const unsigned int newbrt)
	{
		unsigned int i = oldbrt;

		while (i > newbrt) {
      printf("brightness up\n");
			i--;
		}
		while (i < newbrt) {
      printf("brightness down\n");
			i++;
		}
	}

  issue_volchange(0, 5);
  issue_brightnesschange(10, 7);
}
