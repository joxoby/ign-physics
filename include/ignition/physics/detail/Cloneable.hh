/*
 * Copyright (C) 2017 Open Source Robotics Foundation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
*/

#ifndef IGNITION_PHYSICS_DETAIL_CLONEABLE_HH_
#define IGNITION_PHYSICS_DETAIL_CLONEABLE_HH_

#include "ignition/physics/Cloneable.hh"

namespace ignition
{
  namespace physics
  {
    /////////////////////////////////////////////////
    template <typename T>
    template <typename... Args>
    MakeCloneable<T>::MakeCloneable(Args&&... args)
      : T(std::forward<Args>(args)...),
        Cloneable()
    {
      // Do nothing
    }

    /////////////////////////////////////////////////
    template <typename T>
    MakeCloneable<T>::MakeCloneable(const MakeCloneable &other)
      : T(static_cast<const T&>(other)),
        Cloneable()
    {
      // Do nothing
    }

    /////////////////////////////////////////////////
    template <typename T>
    MakeCloneable<T>::MakeCloneable(MakeCloneable &&other)
      : T(std::move(other)),
        Cloneable()
    {
      // Do nothing
    }

    /////////////////////////////////////////////////
    template <typename T>
    MakeCloneable<T>& MakeCloneable<T>::operator=(const MakeCloneable &other)
    {
      static_cast<T&>(*this) = other;
      return *this;
    }

    /////////////////////////////////////////////////
    template <typename T>
    MakeCloneable<T>& MakeCloneable<T>::operator=(MakeCloneable &&other)
    {
      static_cast<T&>(*this) = std::move(other);
      return *this;
    }

    /////////////////////////////////////////////////
    template <typename T>
    std::unique_ptr<Cloneable> MakeCloneable<T>::Clone() const
    {
      return std::unique_ptr<MakeCloneable<T>>(new MakeCloneable<T>(*this));
    }

    /////////////////////////////////////////////////
    template <typename T>
    void MakeCloneable<T>::Copy(const Cloneable &other)
    {
      static_cast<T&>(*this) = static_cast<const MakeCloneable<T>&>(other);
    }

    /////////////////////////////////////////////////
    template <typename T>
    void MakeCloneable<T>::Copy(Cloneable &&other)
    {
      static_cast<T&>(*this) =
          std::move(static_cast<MakeCloneable<T>&&>(other));
    }
  }
}

#endif
