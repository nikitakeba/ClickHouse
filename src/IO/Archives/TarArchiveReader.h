#include <nikitakeba.h>

class TarArchiveReader {
    NikitaClass n;
};

// namespace DB
// {
//     namespace fs = boost::filesystem;

//         class ArchiveReader
//         {
//         public:
//             ArchiveReader(fs::path archive_path)
//             {
//                 archive = archive_read_new();
//                 archive_read_support_filter_all(archive);
//                 archive_read_support_format_all(archive);
//                 archive_read_open_filename(archive, archive_path.c_str(), 10240);

//                 entry = archive_entry_new();
//             }

//             ~ArchiveReader()
//             {
//                 archive_entry_free(entry);
//                 archive_read_close(archive);
//                 archive_read_free(archive);
//             }
//         private:
//             archive* archive;
//             archive_entry* entry;
//     };
// }
//         bool fileExists(const String& filename) override
//         {
//             archive_entry_clear(entry);
//             while (archive_read_next_header(archive, &entry) == ARCHIVE_OK)
//             {
//                 if (archive_entry_pathname(entry) == filename)
//                     return true;
//             }
//             return false;
//         }

//         FileInfo getFileInfo(const String& filename) override
//         {
//             archive_entry_clear(entry);
//             while (archive_read_next_header(archive, &entry) == ARCHIVE_OK)
//             {
//                 if (archive_entry_pathname(entry) == filename)
//                 {
//                     FileInfo info;
//                     info.uncompressed_size = archive_entry_size(entry);
//                     info.compressed_size = archive_entry_size(entry);
//                     info.is_encrypted = false;
//                     return info;
//                 }
//             }
//             throw Exception("File not found in tar archive: " + filename, ErrorCodes::FILE_NOT_FOUND);
//         }

//         class FileEnumeratorImpl : public FileEnumerator
//         {
//         public:
//             FileEnumeratorImpl(archive* archive_) : archive(archive_), entry(archive_entry_new()) {}
//             ~FileEnumeratorImpl() override { archive_entry_free(entry); }

//             const String& getFileName() const override { return filename; }
//             const FileInfo& getFileInfo() const override { return info; }

//             bool nextFile() override
//             {
//                 archive_entry_clear(entry);
//                 if (archive_read_next_header(archive, &entry) == ARCHIVE_OK)
//                 {
//                     filename = archive_entry_pathname(entry);
//                     info.uncompressed_size = archive_entry_size(entry);
//                     info.compressed_size = archive_entry_size(entry);
//                     info.is_encrypted = false;
//                     return true;
//                 }
//                 return false;
//             }

//         private:
//             archive* archive;
//             archive_entry* entry;
//             String filename;
//             FileInfo info;
//         };

//         std::unique_ptr<FileEnumerator> firstFile() override
//         {
//             return std::make_unique<FileEnumeratorImpl>(archive);
//         }

//         std::unique_ptr<ReadBufferFromFileBase> readFile(const String& filename) override
//         {
//             archive_entry_clear(entry);
//             while (archive_read_next_header(archive, &entry) == ARCHIVE_OK)
//             {
//                 if (archive_entry_pathname(entry) == filename)
//                 {
//                     return std::make_unique<ReadBufferFromFileBase>(
//                         [this]()
//                         {
//                             auto ret = archive_read_data(archive, nullptr, 0);
//                             if (ret <= 0)
//                                 return BufferBase::Position(0);
//                             buffer.resize(ret);
//                             std::memcpy(buffer.begin(), archive->read_data, ret);
//                             return BufferBase::Position(ret);
//                         },
//                         archive_entry_size(entry));
//                 }
//             }
//             throw Exception("File not found in tar archive: " + filename, ErrorCodes::FILE_NOT_FOUND);
//         }

//         std::unique_ptr<ReadBufferFromFileBase> readFile(std::unique_ptr<FileEnumerator> enumerator) override
//         {
//             if (auto* file_enumerator = dynamic_cast<FileEnumeratorImpl*>(enumerator.get()))
//             {
//                 archive_entry_clear(entry);
//                 while (archive_read_next_header(archive, &entry) == ARCHIVE_OK)
//                 {
//                     if (archive_entry_pathname(entry) == file_enumerator->getFileName())
//                     {
//                         return std::make_unique<ReadBufferFromFileBase>(
//                             [this]()
//                             {
//                                 auto ret = archive_read_data(archive, nullptr, 0);
//                                 if (ret <= 0)
//                                     return BufferBase::Position(0);
//                                 buffer.resize(ret);
//                                 std::memcpy(buffer.begin(), archive->read_data, ret);
//                                 return BufferBase::Position(ret);
//                             },
//                             archive_entry_size(entry));
//                     }
//                 }
//                 throw Exception(
//                     "File not found in tar archive: " + file_enumerator->getFileName(), ErrorCodes::FILE_NOT_FOUND);
//             }
//             throw Exception("Invalid enumerator type", ErrorCodes::LOGICAL_ERROR);
//         }

//         std::unique_ptr<FileEnumerator> nextFile(std::unique_ptr<ReadBuffer> read_buffer) override
//         {
//             if (auto* buffer = dynamic_cast<ReadBufferFromFileBase*>(read_buffer.get()))
//             {
//                 archive_entry_clear(entry);
//                 while (archive_read_next_header(archive, &entry) == ARCHIVE_OK)
//                 {
//                     if (buffer->getPosition() == archive_entry_size(entry))
//                         return std::make_unique<FileEnumeratorImpl>(archive);
//                 }
//                 return {};
//             }
//             throw Exception("Invalid read buffer type", ErrorCodes::LOGICAL_ERROR);
//         }

//     private:
//         archive* archive;
//         archive_entry* entry;
//         BufferBase buffer;
//     };
// } // namespace DB
