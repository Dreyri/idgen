{ pkgs ? import <nixpkgs> {} }:
with pkgs;

gcc9Stdenv.mkDerivation {
  name = "idgen-dev";

  buildInputs = [];
}
