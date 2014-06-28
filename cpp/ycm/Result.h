// Copyright (C) 2011, 2012  Google Inc.
//
// This file is part of YouCompleteMe.
//
// YouCompleteMe is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// YouCompleteMe is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with YouCompleteMe.  If not, see <http://www.gnu.org/licenses/>.

#ifndef RESULT_H_CZYD2SGN
#define RESULT_H_CZYD2SGN

#include <string>

namespace YouCompleteMe {

class Result {
public:
  Result();
  explicit Result( bool is_subsequence );

  Result( bool is_subsequence,
          const std::string *text,
          int char_match_distance
  );

  inline bool operator< ( const Result &other ) const{
    return char_match_distance_ < other.char_match_distance_;
  }

  inline bool IsSubsequence() const {
    return is_subsequence_;
  }

  inline const std::string *Text() const {
    return text_;
  }

private:

  // true when the characters of the query are a subsequence of the characters
  // in the candidate text, e.g. the characters "abc" are a subsequence for
  // "xxaygbefc" but not for "axxcb" since they occur in the correct order ('a'
  // then 'b' then 'c') in the first string but not in the second.
  bool is_subsequence_;

  // the distance to match the candidate, the front, word begin char, continue chars will get more close
  int char_match_distance_;

  // points to the full candidate text
  const std::string *text_;

};

template< class T >
struct ResultAnd {
  // TODO: Swap the order of these parameters
  ResultAnd( T extra_object, const Result &result )
    : extra_object_( extra_object ), result_( result ) {}

  bool operator< ( const ResultAnd &other ) const {
    return result_ < other.result_;
  }

  T extra_object_;
  Result result_;
};

template< class T >
struct ResultAnd<T * > {
  ResultAnd( const T *extra_object, const Result &result )
    : extra_object_( extra_object ), result_( result ) {}

  bool operator< ( const ResultAnd &other ) const {
    return result_ < other.result_;
  }

  const T *extra_object_;
  Result result_;
};

} // namespace YouCompleteMe

#endif /* end of include guard: RESULT_H_CZYD2SGN */

