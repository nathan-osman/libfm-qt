#ifndef FM2_DIRLISTJOB_H
#define FM2_DIRLISTJOB_H

#include "libfmqtglobals.h"
#include <mutex>
#include "job.h"
#include "filepath.h"
#include "gobjectptr.h"
#include "fileinfo.h"

namespace Fm2 {

class LIBFM_QT_API DirListJob : public Job {
    Q_OBJECT
public:
   enum Flags {
       FAST = 0,
       DIR_ONLY = 1 << 0,
       DETAILED = 1 << 1
   };

    explicit DirListJob(const FilePath& path, Flags flags);

    FileInfoList& files() {
        return files_;
    }

    void setIncremental(bool set);

    bool incremental() const {
        return emit_files_found;
    }

    void run() override;

Q_SIGNALS:
    void filesFound(FileInfoList& foundFiles);

private:
    std::mutex mutex_;
    FilePath dir_path;
    Flags flags;
    std::shared_ptr<const FileInfo> dir_fi;
    FileInfoList files_;
    bool emit_files_found;
    // guint delay_add_files_handler;
    // GSList* files_to_add;
};

} // namespace Fm2

#endif // FM2_DIRLISTJOB_H
