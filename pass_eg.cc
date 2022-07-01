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
#include <act/act.h>
#include "pass_eg.h"


void pass_test_init (ActPass *ap)
{
  printf ("Hello, initialized pass!\n");
}

/* Not defining this
void pass_test_run (ActPass *ap, Process *p);
void pass_test_recursive (ActPass *ap, Process *p, int mode);
*/

void *pass_test_proc (ActPass *ap, Process *p, int mode)
{
  char * s= NULL;

  if (!p) {
    /* run on the top level global namespace */
    printf ("Visiting global namespace\n");
    return NULL;
  }
  
  if (p->getns() != ActNamespace::Global()) {
    s = p->getns()->Name(true);
  }
  printf ("Visiting process %s%s, mode %d\n", s ? s : "", p->getName(), mode);
  if (s) {
    FREE (s);
  }
  return NULL;
}

void *pass_test_data (ActPass *ap, Data *d, int mode)
{
  char * s= NULL;
  if (d->getns() != ActNamespace::Global()) {
    s = d->getns()->Name(true);
  }
  printf ("Visiting datatype %s%s, mode %d\n", s ? s : "", d->getName(), mode);
  if (s) {
    FREE (s);
  }
  return NULL;
}

void *pass_test_chan (ActPass *ap, Channel *c, int mode)
{
  char * s= NULL;
  if (c->getns() != ActNamespace::Global()) {
    s = c->getns()->Name(true);
  }
  printf ("Visiting channel type %s%s, mode %d\n", s ? s : "", c->getName(), mode);
  if (s) {
    FREE (s);
  }
  return NULL;
}

int pass_test_runcmd (ActPass *ap, const char *name)
{
  int p;
  ActDynamicPass *dp;
  printf ("received commmand %s\n", name ? name : "null");

  dp = dynamic_cast<ActDynamicPass *> (ap);
  Assert (dp, "This is a dynamic pass, what happened?!");

  p = dp->getIntParam ("argtest");
  printf ("  argtest = %d\n", p);
  
  return 1;
}

void pass_test_free (ActPass *ap, void *v)
{
  /* this should be NULL, ignore it */
}


void pass_test_done (ActPass *ap)
{
  printf ("Pass deleted!\n");
}
