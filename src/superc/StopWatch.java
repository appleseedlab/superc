/*
 * xtc - The eXTensible Compiler
 * Copyright (C) 2009-2012 New York University
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * version 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301,
 * USA.
 */
package xtc.lang.cpp;

/**
 * A stopwatch-style timer.
 *
 * @author Paul Gazzillo
 */
public class StopWatch {
  /** The cumulative total time. */
  long total;

  /** The start time. */
  long start;

  /** Whether timing or not. */
  boolean isTiming;

  /** Create a new stopwatch. */
  public StopWatch() {
    this.total = 0;
    this.isTiming = false;
  }

  /** Start timing. */
  public void start() {
    if (isTiming) throw new IllegalStateException();

    isTiming = true;
    start = System.currentTimeMillis();
  }

  /** Stop timing. */
  public void stop() {
    if (! isTiming) throw new IllegalStateException();

    total += System.currentTimeMillis() - start;
    isTiming = false;
  }

  /**
   * Get the cumulative total in milliseconds.
   *
   * @return The cumulative total in milliseconds.
   */
  public long getTotalMillis() {
    return total;
  }

  /**
   * Get the cumulative total in seconds.
   *
   * @return The cumulative total in seconds.
   */
  public double getTotalSeconds() {
    return ((double)total) / 1000.;
  }
}
