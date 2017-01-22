let
  pkgs = import <nixpkgs> {};
  stdenv = pkgs.stdenv;
in rec {
  guiletoy = stdenv.mkDerivation rec {
    name = "browser";
    version = "0.0.1";
    src = ./.;
    buildInputs = [ pkgs.pkgconfig pkgs.gnome3.gtk pkgs.guile ];
    C_INCLUDE_PATH = "${pkgs.guile}/include/guile/2.0/";
  };
}
