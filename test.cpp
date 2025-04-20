template <typename T>
concept test = requires { static_cast<int>(T()); };
