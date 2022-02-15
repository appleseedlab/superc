#ifdef ENABLE_AUTO_BED_LEVELING
#define AUTO_BED_LEVELING_GRID

#ifdef AUTO_BED_LEVELING_GRID

// set the rectangle in which to probe
#define LEFT_PROBE_BED_POSITION 15

#else  // not AUTO_BED_LEVELING_GRID
// with no grid, just probe 3 arbitrary points.  A simple cross-product
// is used to esimate the plane of the print bed
  #define ABL_PROBE_PT_1_X 15

#endif // AUTO_BED_LEVELING_GRID
#endif // AUTO_BED_LEVELING


void process_commands(){

  #ifdef ENABLE_AUTO_BED_LEVELING
  int left_probe_bed_position=LEFT_PROBE_BED_POSITION; // ERROR

  #ifdef AUTO_BED_LEVELING_GRID
  int xGridSpacing = left_probe_bed_position;
  #else
  float z_at_pt_1, z_at_pt_2, z_at_pt_3;
  #endif
#endif
}

int main(int argc, char** argv)
{
  process_commands();
  return 0;
}
