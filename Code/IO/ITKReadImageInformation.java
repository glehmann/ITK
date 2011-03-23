
import java.io.IOException;
import loci.formats.*;
import loci.formats.meta.MetadataRetrieve;
import loci.formats.meta.MetadataStore;
import java.io.FileOutputStream;
import java.util.Iterator;
import java.util.Set;
import java.util.Map;
import java.util.HashMap;

public final class ITKReadImageInformation {

  // -- Constructor --

  private ITKReadImageInformation() { }

  // -- Utility methods --

  /** A utility method for converting a file from the command line. */
  public static boolean testConvert(String[] args)
    throws FormatException, IOException
  {
    IFormatReader reader = new ImageReader();
//    reader = new ChannelSeparator(reader);

    reader.setMetadataFiltered(true);
    reader.setOriginalMetadataPopulated(true);
    MetadataStore store = MetadataTools.createOMEXMLMetadata();
    if (store == null) System.err.println("OME-Java library not found.");
    else reader.setMetadataStore(store);

    reader.setGroupFiles(false); // avoid grouping all the .lsm when a .mdb is there
    reader.setId(args[0]);
    reader.setSeries(0);

     store = reader.getMetadataStore();
    MetadataRetrieve meta = (MetadataRetrieve) store;

   // now print the informations

   // little endian?
    System.out.println( "LittleEndian(bool): " + (reader.isLittleEndian()? 1:0) );

    // component type
    // set ITK component type
    int pixelType = reader.getPixelType();
    int itkComponentType;
    if( pixelType == FormatTools.UINT8 )
      {
      itkComponentType = 1;
      }
    else if( pixelType == FormatTools.INT8 )
      {
      itkComponentType = 2;
      }
    else if( pixelType == FormatTools.UINT16 )
      {
      itkComponentType = 3;
      }
    else if( pixelType == FormatTools.INT16 )
      {
      itkComponentType = 4;
      }
    else if( pixelType == FormatTools.UINT32 )
      {
      itkComponentType = 5;
      }
    else if( pixelType == FormatTools.INT32 )
      {
      itkComponentType = 6;
      }
    else if( pixelType == FormatTools.FLOAT )
      {
      itkComponentType = 9;
      }
    else if( pixelType == FormatTools.DOUBLE )
      {
      itkComponentType = 10;
      }
    else
      {
      itkComponentType = 0;
      }
    System.out.println( "PixelType(enum): " + itkComponentType );

    // x, y, z, t, c
    System.out.println( "SizeX(int): " + reader.getSizeX() );
    System.out.println( "SizeY(int): " + reader.getSizeY() );
    System.out.println( "SizeZ(int): " + reader.getSizeZ() );
    System.out.println( "SizeT(int): " + reader.getSizeT() );
    System.out.println( "SizeC(int): " + reader.getEffectiveSizeC() ); // reader.getSizeC()

    // number of components
    System.out.println( "RGBChannelCount(int): " + reader.getRGBChannelCount() );

    // spacing
    System.out.println( "PixelsPhysicalSizeX(real): " + (meta.getPixelsPhysicalSizeX(0)==null? 1.0: meta.getPixelsPhysicalSizeX(0)) );
    System.out.println( "PixelsPhysicalSizeY(real): " + (meta.getPixelsPhysicalSizeY(0)==null? 1.0: meta.getPixelsPhysicalSizeY(0)) );
    System.out.println( "PixelsPhysicalSizeZ(real): " + (meta.getPixelsPhysicalSizeZ(0)==null? 1.0: meta.getPixelsPhysicalSizeZ(0)) );
    System.out.println( "PixelsPhysicalSizeT(real): " + (meta.getPixelsTimeIncrement(0)==null? 1.0: meta.getPixelsTimeIncrement(0)) );
    System.out.println( "PixelsPhysicalSizeC(real): " + 1.0 ); // should we give something more useful for this one?

    HashMap<String, Object> metadata = new HashMap<String, Object>();
    metadata.putAll( reader.getGlobalMetadata() );
    metadata.putAll( reader.getSeriesMetadata() );
    Set entries = metadata.entrySet();
    Iterator it = entries.iterator();
    while (it.hasNext()) {
      Map.Entry entry = (Map.Entry) it.next();

      String key = (String)entry.getKey();
      Object value = entry.getValue();

      // clean up the key name
      key = key.replace('(', ' ');
      key = key.replace(')', ' ');
      key = key.replace(':', ' ');

      String type;
      if( value instanceof Double )
        {
        type = "real";
        }
      else if( value instanceof Long )
        {
        type = "int";
        }
      else if( value instanceof Integer )
        {
        type = "int";
        }
      else if( value instanceof Boolean )
        {
        type = "bool";
        // don't print false or true, but 0 or 1
        if( ((Boolean)value).booleanValue() )
          {
          value = new Integer(1);
          }
        else
          {
          value = new Integer(0);
          }
        }
      else if( value instanceof String )
        {
        // remove the line return
        value = ((String)value).replace("\\", "\\\\").replace("\n", "\\n");
        type = "string";
        }
      else
        {
        // defaults to string
        type = "string";
        }
      System.out.println( entry.getKey() + "("+type+"): " + value );
    }

    return true;
  }

  // -- Main method --

  public static void main(String[] args) throws FormatException, IOException {
    if (!testConvert(args)) System.exit(1);
  }

}
