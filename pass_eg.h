/*************************************************************************
 *
 *  This file is part of the ACT example pass implementation
 *
 *  Copyright (c) 2022 Rajit Manohar
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 **************************************************************************
 */
#ifndef __ACT_TEST_PASS_H__
#define __ACT_TEST_PASS_H__


/**
 * 
 * @file pass_eg.h
 * @brief An example ACT pass.
 *
 * This module provides an example of implementing an ACT
 * pass that can be dynamically loaded into the interact framework.
 *
 * An ACT pass implements a number of functions detailed in this
 * example, with a specific naming convention.  Any of the functions
 * below can be omitted, although if the init function is omitted
 * you will receive a warning.
 * 
 * The functions below use the "pass_test" prefix. This prefix
 * should be modified for your own pass implementation.
 *
 * An ACT pass operates on the expanded ACT design. The pass
 * operates on user-defined types (processes, channels,
 * datatypes). The two common use cases are:
 *
 *  - a pass operates on a type and saves some data about it
 *
 *	- a pass operates on a type and changes its internal data
 *	  stucture
 *
 * The "_proc", "_chan", and "_data" functions defined are used for
 * this purpose. They return a void pointer that is saved away with
 * the specified process. This pointer can be retrieved using the
 * standard getMap() method for any ACT pass.
 *
 * An Act pass runs on the entire design hierarchy, where each
 * unique user-defined type (process, channel, data) has the pass
 * invoked once. The invocation order guarantees that any instances
 * within a type will have their pass called first. So the leaves of
 * the instance hierarchy will have their pass called first,
 * followed by their parents, and so on until the root of the
 * design.
 */


extern "C" {

  /**
   *    @fn pass_test_init (ActPass *ap)
   *    @param ap The ActPass structure corresponding to this pass. It
   *    will be of type ActDynamicPass.
   *
   *    This is called once to initialize the pass for the design.
   *    Use this function to initialize data structures, read
   *    configuration options, etc.
   *
   *    The "ActPass" pointer can be used to communicate information from
   *    the core act infrastructure to your pass.
   */
  void pass_test_init (ActPass *ap);


  /**
   * @fn pass_test_run (ActPass *ap, Process *p);
   * @param ap The ActPass pointer corresponding to this pass.
   * @param p The expanded top-level process to operate on.
   *
   * This is the main function that is called right after a pass is run.
   * Normally this can be left undefined, as the default function
   * "does the right thing."
   */
  void pass_test_run (ActPass *ap, Process *p);


  /**
   *    @fn pass_test_recursive (ActPass *ap, Process *p, int mode);
   * @param ap The ActPass pointer corresponding to this pass.
   * @param p The expanded top-level process to operate on.
   * @param mode An integer (greater than zero) used to specify the
   * run mode.
   *
   * ACT also permitts multiple "modes" in which a pass can be
   * run. (e.g. compute some data structure, print out debugging
   * information, etc). These modes are invoked using the run_recursive
   * method call, with a "mode" parameter. So this is like run, but
   * with an additional parameter. This, also, can normally be left
   * undefined.
   */
  void pass_test_recursive (ActPass *ap, Process *p, int mode);


  /**
   *    @fn pass_test_proc (ActPass *ap, Process *p, int mode);
   * @param ap The ActPass pointer corresponding to this pass.
   * @param p The expanded process to operate on.
   * @param mode An integer used to specify the run mode (0 = normal).
   * @return a data structure that can be retrieved using the getMap()
   * method applied to the process pointer at a later time.
   *
   * For each user-defined type, this returns any data structure that
   * is built using this particular pass. This can be retrieved using
   * the getMap() method.
   *    
   * The "mode" parameter is used to distinguish between invocations
   * via "pass_test_run and "pass_test_recursive"; mode is set to 0 for
   * the "_run" case, and is a pass-through parameter for "_recursive".
   */
  void *pass_test_proc (ActPass *ap, Process *p, int mode);


  /**
   *    @fn pass_test_data (ActPass *ap, Data *d, int mode);
   * @param ap The ActPass pointer corresponding to this pass.
   * @param d The expanded user-defined datatype to operate on.
   * @param mode An integer (greater than zero) used to specify the run mode.
   * @return a data structure that can be retrieved using the getMap()
   * method applied to the Data pointer at a later time.
   *
   * Similar to pass_test_proc(), but for user-defined data-types.
   */
  void *pass_test_data (ActPass *ap, Data *d, int mode);


  /**
   *    @fn pass_test_chan (ActPass *ap, Channel *c, int mode);
   * @param ap The ActPass pointer corresponding to this pass.
   * @param d The expanded user-defined datatype to operate on.
   * @param mode An integer (greater than zero) used to specify the
   * run mode.
   * @return a data structure that can be retrieved using the getMap()
   * method applied to the Channel pointer at a later time.
   *
   * Similar to pass_test_proc(), but for user-defined data-types.
   */
  void *pass_test_chan (ActPass *ap, Channel *c, int mode);


  /**
   *    @fn pass_test_runcmd (ActPass *ap, const char *name);
   * @param ap The ActPass pointer corresponding to this pass.
   * @param name A string corresponding to the command to be executed.
   * @return 1 to return true, 0 to return false, anything else for error.
   *
   * This function is used for any generic commands you might want to
   * include in a pass.
   * 
  */
  int pass_test_runcmd (ActPass *ap, const char *name);


  /**
   *    @fn pass_test_free (ActPass *ap, void *v);
   * @param ap The ActPass pointer corresponding to this pass.
   * @param v  A pointer returned by the _proc/_chan/_data functions.
   *
   * Release storage for the allocated data structure associated with a
   * particular process/data/channel type.
   */
  void pass_test_free (ActPass *ap, void *v);


  /**
   *    @fn pass_test_done  (ActPass *ap);
   * @param ap The ActPass pointer corresponding to this pass.
   *
   * Clean up all storage for the pass; called when the pass is destroyed.
  */
  void pass_test_done (ActPass *ap);

}

#endif /* __ACT_TEST_PASS_H__ */
