
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

    int xBegin = Integer.parseInt( args[1] );
    int xEnd =   Integer.parseInt( args[2] ) + xBegin - 1;
    int yBegin = Integer.parseInt( args[3] );
    int yEnd =   Integer.parseInt( args[4] ) + yBegin - 1;
    int zBegin = Integer.parseInt( args[5] );
    int zEnd =   Integer.parseInt( args[6] ) + zBegin - 1;
    int tBegin = Integer.parseInt( args[7] );
    int tEnd =   Integer.parseInt( args[8] ) + tBegin - 1;
    int cBegin = Integer.parseInt( args[9] );
    int cEnd =   Integer.parseInt( args[10] ) + cBegin - 1;

    int rgbChannelCount = reader.getRGBChannelCount();
    int bpp = FormatTools.getBytesPerPixel( reader.getPixelType() );
    int xCount = reader.getSizeX();
    int yCount = reader.getSizeY();
    boolean isInterleaved = reader.isInterleaved();
    boolean canDoDirect = xBegin == 0 && yBegin == 0 && xEnd == xCount-1 && yEnd == yCount-1 && rgbChannelCount == 1;

    BufferedOutputStream out = new BufferedOutputStream(System.out);

    for( int c=cBegin; c<=cEnd; c++ )
      {
      for( int t=tBegin; t<=tEnd; t++ )
        {
        for( int z=zBegin; z<=zEnd; z++ )
          {
          byte[] image = reader.openBytes( reader.getIndex(z, c, t) );
          if( canDoDirect )
            {
            out.write(image);
            }
          else
            {
            for( int y=yBegin; y<=yEnd; y++ )
              {
              for( int x=xBegin; x<=xEnd; x++ )
                {
                for( int i=0; i<rgbChannelCount; i++ )
                  {
                  for( int b=0; b<bpp; b++ )
                    {
                    int index = xCount * (yCount * (rgbChannelCount * b + i) + y) + x;
                    out.write( image[index] );
                    }
                  }
                }
              }
            }
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
