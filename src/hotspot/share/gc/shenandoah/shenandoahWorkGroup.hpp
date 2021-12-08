/*
 * Copyright (c) 2017, 2021, Red Hat, Inc. All rights reserved.
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 *
 * This code is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License version 2 only, as
 * published by the Free Software Foundation.
 *
 * This code is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 * version 2 for more details (a copy is included in the LICENSE file that
 * accompanied this code).
 *
 * You should have received a copy of the GNU General Public License version
 * 2 along with this work; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 * Please contact Oracle, 500 Oracle Parkway, Redwood Shores, CA 94065 USA
 * or visit www.oracle.com if you need additional information or have any
 * questions.
 *
 */

#ifndef SHARE_GC_SHENANDOAH_SHENANDOAHWORKGROUP_HPP
#define SHARE_GC_SHENANDOAH_SHENANDOAHWORKGROUP_HPP

#include "gc/shared/workerThread.hpp"
#include "gc/shenandoah/shenandoahTaskqueue.hpp"
#include "memory/allocation.hpp"

class ShenandoahObjToScanQueueSet;

class ShenandoahWorkerScope : public StackObj {
private:
  uint      _n_workers;
  WorkerThreads* _workers;
public:
  ShenandoahWorkerScope(WorkerThreads* workers, uint nworkers, const char* msg, bool do_check = true);
  ~ShenandoahWorkerScope();
};

class ShenandoahPushWorkerScope : StackObj {
protected:
  uint      _n_workers;
  uint      _old_workers;
  WorkerThreads* _workers;

public:
  ShenandoahPushWorkerScope(WorkerThreads* workers, uint nworkers, bool do_check = true);
  ~ShenandoahPushWorkerScope();
};

class ShenandoahWorkerThreads : public WorkerThreads {
private:
  bool     _initialize_gclab;
public:
  ShenandoahWorkerThreads(const char* name,
           uint workers) :
    WorkerThreads(name, workers), _initialize_gclab(false) {
    }

  // Create a GC worker.
  // We need to initialize gclab for dynamic allocated workers
  WorkerThread* create_worker(uint which);

  void set_initialize_gclab() { assert(!_initialize_gclab, "Can only enable once"); _initialize_gclab = true; }
};

#endif // SHARE_GC_SHENANDOAH_SHENANDOAHWORKGROUP_HPP
