let
  pkgs = import <nixpkgs> {};
  stdenv = pkgs.stdenv;
  glib_networking = pkgs.glib_networking;
in rec {
  luna = stdenv.mkDerivation rec {
    name = "luna";
    version = "0.0.1";
    src = ./.;
    buildInputs = [ pkgs.pkgconfig
                    pkgs.gnome3.gtk
		    pkgs.gnome3.webkitgtk
		    pkgs.guile
		    pkgs.gsettings_desktop_schemas
		    pkgs.makeWrapper ];

    makeFlags = [ "PREFIX=$(out)" ];

    preFixup = ''
      wrapProgram "$out/bin/luna" \
        --prefix GIO_EXTRA_MODULES : "${glib_networking.out}/lib/gio/modules" \
	--prefix XDG_DATA_DIRS : "$GSETTINGS_SCHEMAS_PATH"
    '';
    
  };
}
