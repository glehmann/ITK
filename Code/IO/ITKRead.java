
import java.io.IOException;
import loci.formats.*;
import loci.formats.in.DefaultMetadataOptions;
import loci.formats.in.MetadataLevel;
import java.io.BufferedOutputStream;

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

    for( int c=0; c<reader.getSizeC(); c++ )
      {
      for( int t=0; t<reader.getSizeT(); t++ )
        {
        for( int z=0; z<reader.getSizeZ(); z++ )
          {
          byte[] image = reader.openBytes( reader.getIndex(z, c, t) );
          out.write(image);
          }
        }
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
