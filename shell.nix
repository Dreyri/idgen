{ pkgs ? import <nixpkgs> {} }:
with pkgs;
let
  nameof = callPackage ./nix/nameof.nix { };
in
gcc9Stdenv.mkDerivation {
  name = "idgen-dev";

  buildInputs = [ nameof ];
}
