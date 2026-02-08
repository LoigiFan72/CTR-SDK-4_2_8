/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     snd_Bcwav.h

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

#ifndef NN_SND_BCWAV_H_
#define NN_SND_BCWAV_H_

#include <nn/snd/CTR/Common/snd_Adpcm.h>

/* Please see man pages for details 
    
*/

#ifdef __cplusplus

namespace nn { namespace snd { namespace CTR {

/* Please see man pages for details 
    
 */
class Bcwav {
private:
    Bcwav() {}
    ~Bcwav() {}

public:
    // --- Basic types ---
    struct Reference
    {
        u16 typeId;     // Non-public to users
        u16 padding;
        u32 offset;
    };

    struct ReferenceWithSize : public Reference
    {
        u32 size;
    };

    template< typename ITEM_TYPE >
    struct Table
    {
        u32 count;
        ITEM_TYPE item[1];
    };

    // --- File data structure ---
    struct FileHeader
    {
        u32 signature;          // Always 'CWAV'
        u16 byteOrderMark;
        u16 headerSize;
        u32 version;
        u32 fileSize;
        u16 dataBlocks;
        u16 reserved;
    };

    struct BlockInfo
    {
        ReferenceWithSize infoBlockReference;
        ReferenceWithSize dataBlockReference;
    };

    struct FileInfo
    {
        FileHeader header;
        BlockInfo  blockInfo;
    };

    // --- Block data structure ---
    struct BlockHeader
    {
        u32 kind;       // 'INFO' or 'DATA'
        u32 size;
    };

    /* Please see man pages for details 
        
     */
    struct WaveInfo
    {
        u8  encoding;           //
        u8  isLoop;             //
        u16 padding;
        u32 sampleRate;         //
        u32 loopStartFrame;     //
        u32 loopEndFrame;       //
    };

    struct InfoBlockBody
    {
        WaveInfo waveInfo;
        u32 reserved;
        Table<Reference> channelInfoReferenceTable;
    };

    struct ChannelInfo
    {
        Reference toSamples;    // Origin is data block body (after BlockHeader)
        Reference toAdpcmInfo;
        u32 reserved;
    };

    /* Please see man pages for details 
        
     */
    struct DspAdpcmInfo
    {
        AdpcmParam     param;          //
        AdpcmContext   context;        //
        AdpcmContext   loopContext;    //
    };

    /* Please see man pages for details 
        
        
     */
    struct ImaAdpcmContext
    {
        s16 data;
        u8  tableIndex;
        u8  padding;
    };
    
    /* Please see man pages for details 
        
        
     */
    struct ImaAdpcmInfo
    {
        ImaAdpcmContext   context;        //
        ImaAdpcmContext   loopContext;    //
    };

    struct InfoBlock
    {
        BlockHeader header;
        InfoBlockBody body;
    };

    /* Please see man pages for details 
        
     */
    typedef enum
    {
        ENCODING_PCM8      = 0,    //
        ENCODING_PCM16     = 1,    //
        ENCODING_DSP_ADPCM = 2,    //
        ENCODING_IMA_ADPCM = 3,    //
        ENCODING_NUM       = 4
    } Encoding;

    /* Please see man pages for details 
        
     */
    typedef enum
    {
        CHANNEL_INDEX_L = 0,       //
        CHANNEL_INDEX_R = 1        //
    } ChannelIndex;

    /* Please see man pages for details 
      
      
     */
    /* Please see man pages for details 
        
        
        
     */
    static const WaveInfo& GetWaveInfo(const void* bcwav);

    /* Please see man pages for details 
        
        
        
     */
    static int GetChannelCount(const void* bcwav);

    /* Please see man pages for details 
        
        
        
        
     */
    static const void* GetWave(const void* bcwav, int channelNo);

    /* Please see man pages for details 
        
        
        
        
     */
    static const DspAdpcmInfo* GetDspAdpcmInfo(const void* bcwav, int channelNo);

    /* Please see man pages for details 
        
        
        
        
        
     */
    static const ImaAdpcmContext* GetImaAdpcmContext(const void* bcwav, int channelNo);

    /* Please see man pages for details 
        
        
        
        
        
     */
    static const ImaAdpcmContext* GetImaAdpcmLoopContext(const void* bcwav, int channelNo);

    /* Please see man pages for details 
        
        
        
        
     */
    static u32 FrameToByte(u8 encoding, u32 frame);

    /* Please see man pages for details 
        
        
        
        
     */
    static const void* AddOffsetToPtr(const void* ptr, int offset);

    /* Please see man pages for details 
        
        
        
     */
    static bool IsBcwav(const void* bcwav);

    /*  

*/
};

}}} // namespace nn::snd::CTR

#endif // __cplusplus

typedef enum
{
    NN_SND_BCWAV_ENCODING_PCM8      = 0,    //
    NN_SND_BCWAV_ENCODING_PCM16     = 1,    //
    NN_SND_BCWAV_ENCODING_DSP_ADPCM = 2,    //
    NN_SND_BCWAV_ENCODING_IMA_ADPCM = 3,    //
    NN_SND_BCWAV_ENCODING_NUM       = 4
} nnsndBcwavEncoding;

typedef enum
{
    NN_SND_BCWAV_CHANNEL_INDEX_L = 0,       //
    NN_SND_BCWAV_CHANNEL_INDEX_R = 1        //
} nnsndBcwavChannelIndex;

#endif /* NN_SND_BCWAV_H_ */

