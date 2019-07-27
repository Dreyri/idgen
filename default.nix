{ pkgs ? import <nixpkgs> { } }:
with pkgs;
let
  nameof = callPackage ./nix/nameof.nix { };
in
callPackage ./derivation.nix { nameof = nameof; }
