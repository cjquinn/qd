#pragma once

namespace qd::store {
template <class Payload>
struct Action {
  Payload payload;
};
}  // namespace qd::store
