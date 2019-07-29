{ stdenv, cmake, fetchurl, callPackage }:
let
  nameof = callPackage ./nix/nameof.nix { };
in
stdenv.mkDerivation rec {
  name = "idgen-${version}";
  version = "git";
  
  src = ./.;
  
  nativeBuildInputs = [ cmake ];
  propagatedBuildInputs = [ nameof ];
  
  meta = with stdenv.lib; {
    homepage = "https://github.com/dreyri/idgen";
    description = "Efficiently generate unique global ids for types, without RTTI";
    license = licenses.mit;
  };
}
