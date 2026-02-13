#ifndef PRECOND_VIOLATED_EXCEP_H
#define PRECOND_VIOLATED_EXCEP_H

#include <stdexcept>
#include <string>

// HATA SEBEBİ: Eskiden constructor burada inline tanımlanmıştı, şimdi sadece bildiriyoruz!
class PrecondViolatedExcep : public std::logic_error {
public:
    explicit PrecondViolatedExcep(const std::string& message = "Precondition Violated Exception");
};

#endif // PRECOND_VIOLATED_EXCEP_H
