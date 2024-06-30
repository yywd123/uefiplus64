#pragma once

namespace efi {

template <typename R, typename... P> using Function = R (*)(P...);

} // namespace efi