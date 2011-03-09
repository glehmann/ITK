//
// ImageConverter.java
//

/*
OME Bio-Formats package for reading and converting biological file formats.
Copyright (C) 2005-@year@ UW-Madison LOCI and Glencoe Software, Inc.

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/


import java.io.IOException;
import loci.formats.*;
import loci.formats.in.DefaultMetadataOptions;
import loci.formats.in.MetadataLevel;
import java.io.BufferedOutputStream;

/**
 * ImageConverter is a utility class for converting a file between formats.
 *
 * <dl><dt><b>Source code:</b></dt>
 * <dd><a href="https://skyking.microscopy.wisc.edu/trac/java/browser/trunk/loci/formats/tools/ImageConverter.java">Trac</a>,
 * <a href="https://skyking.microscopy.wisc.edu/svn/java/trunk/loci/formats/tools/ImageConverter.java">SVN</a></dd></dl>
 */
public final class ITKRead {

  // -- Constructor --

  private ITKRead() { }

  // -- Utility methods --

  /** A utility method for converting a file from the command line. */
  public static boolean testConvert(String[] args)
    throws FormatException, IOException
  {
    IFormatReader reader = new ImageReader();
    reader.setMetadataOptions(new DefaultMetadataOptions(MetadataLevel.MINIMUM));
    reader.setGroupFiles(false); // avoid grouping all the .lsm when a .mdb is there
    reader.setId(args[0]);
    reader.setSeries(0);

    BufferedOutputStream out = new BufferedOutputStream(System.out);

    for( int z=0; z<reader.getSizeZ(); z++ )
      {
      byte[] image = reader.openBytes( reader.getIndex(z, 0, 0) );
      out.write(image);
      }
    out.close();
    System.out.close();
    return true;
  }

  // -- Main method --

  public static void main(String[] args) throws FormatException, IOException {
    if (!testConvert(args)) System.exit(1);
  }

}
