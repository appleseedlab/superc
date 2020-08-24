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
package superc.core;

import superc.core.ForkMergeParser.Subparser;

/**
 * The interface to the semantic action plugin.
 *
 * @author Paul Gazzillo
 * @version $Revision: 1.4 $
 */
public interface SemanticActions {
  /**
   * Invoke an action inlined in a production.
   *
   * @param production The production number.
   * @param subparser The subparser invoking the action.
   */
  public Object action(int production, Subparser subparser, Object value);

  /**
   * Dispatch a semantic action.
   *
   * @param id The symbol id.
   * @param subparser The subparser invoking the action.
   */
  public void dispatch(int id, Subparser subparser);
}
