{ stdenv, cmake, fetchurl }:
stdenv.mkDerivation rec {
  name = "nameof-${version}";
  version = "0.9.0";

  src = fetchurl {
    url = "https://github.com/Neargye/nameof/archive/v0.9.0.tar.gz";
    sha256 = "0wdc0zm8rlwykwfqyhpxfkyravr69dp7yvrx19n2kk9kz5prw76g";
  };

  nativeBuildInputs = [ cmake ];
}
