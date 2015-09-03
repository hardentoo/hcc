/**
 * Effects: Assigns through each iterator i in [result,result + (last - first))
 * the value of GENERALIZED_NONCOMMUTATIVE_SUM(binary_op, unary_op(*first), ..., unary_op(*(first + (i - * result))))
 * or GENERALIZED_NONCOMMUTATIVE_SUM(binary_op, init, unary_op(*first), ..., unary_op(*(first + (i * - result)))) if init is provided.
 *
 * Return: The end of the resulting range beginning at result.
 *
 * Requires: Neither unary_op nor binary_op shall invalidate iterators or
 * subranges, or modify elements in the ranges [first,last) or
 * [result,result + (last - first)).
 *
 * Complexity: O(last - first) applications each of unary_op and binary_op.
 *
 * Notes: The difference between transform_exclusive_scan and
 * transform_inclusive_scan is that transform_inclusive_scan includes the ith
 * input element from the ith sum. If binary_op is not mathematically
 * associative, the behavior of transform_inclusive_scan may be nondeterministic.
 * transform_inclusive_scan does not apply unary_op to init.
 */
template<typename InputIterator, typename OutputIterator,
         typename UnaryOperation, typename BinaryOperation, typename T,
         utils::EnableIf<utils::isInputIt<InputIterator>> = nullptr>
OutputIterator
transform_inclusive_scan(InputIterator first, InputIterator last,
                         OutputIterator result,
                         UnaryOperation unary_op,
                         BinaryOperation binary_op, T init) {
  // invoke std::experimental::parallel::transform and
  //        std::experimental::parallel::inclusive_scan
  transform(par, first, last, result, unary_op);
  const size_t N = static_cast<size_t>(std::distance(first, last));
  return inclusive_scan(par, result, result + N, result, binary_op, init);
}

/**
 * Effects: Assigns through each iterator i in [result,result + (last - first))
 * the value of GENERALIZED_NONCOMMUTATIVE_SUM(binary_op, unary_op(*first), ..., unary_op(*(first + (i - * result))))
 * or GENERALIZED_NONCOMMUTATIVE_SUM(binary_op, init, unary_op(*first), ..., unary_op(*(first + (i * - result)))) if init is provided.
 *
 * Return: The end of the resulting range beginning at result.
 *
 * Requires: Neither unary_op nor binary_op shall invalidate iterators or
 * subranges, or modify elements in the ranges [first,last) or
 * [result,result + (last - first)).
 *
 * Complexity: O(last - first) applications each of unary_op and binary_op.
 *
 * Notes: The difference between transform_exclusive_scan and
 * transform_inclusive_scan is that transform_inclusive_scan includes the ith
 * input element from the ith sum. If binary_op is not mathematically
 * associative, the behavior of transform_inclusive_scan may be nondeterministic.
 * transform_inclusive_scan does not apply unary_op to init.
 */
template<typename ExecutionPolicy,
         typename InputIterator, typename OutputIterator,
         typename UnaryOperation, typename BinaryOperation, typename T,
         utils::EnableIf<utils::isExecutionPolicy<ExecutionPolicy>> = nullptr,
         utils::EnableIf<utils::isInputIt<InputIterator>> = nullptr>
OutputIterator
transform_inclusive_scan(ExecutionPolicy&& exec,
               InputIterator first, InputIterator last,
               OutputIterator result,
               UnaryOperation unary_op,
               BinaryOperation binary_op, T init) {
  if (utils::isParallel(exec)) {
    return transform_inclusive_scan(first, last, result, unary_op, binary_op, init);
  } else {
    details::transform_impl(first, last, result, unary_op,
      std::input_iterator_tag{});
    const size_t N = static_cast<size_t>(std::distance(first, last));
    return details::inclusive_scan_impl(result, result + N, result, binary_op, init,
             std::input_iterator_tag{});
  }
}

/**
 * Effects: Assigns through each iterator i in [result,result + (last - first))
 * the value of GENERALIZED_NONCOMMUTATIVE_SUM(binary_op, unary_op(*first), ..., unary_op(*(first + (i - * result))))
 * or GENERALIZED_NONCOMMUTATIVE_SUM(binary_op, init, unary_op(*first), ..., unary_op(*(first + (i * - result)))) if init is provided.
 *
 * Return: The end of the resulting range beginning at result.
 *
 * Requires: Neither unary_op nor binary_op shall invalidate iterators or
 * subranges, or modify elements in the ranges [first,last) or
 * [result,result + (last - first)).
 *
 * Complexity: O(last - first) applications each of unary_op and binary_op.
 *
 * Notes: The difference between transform_exclusive_scan and
 * transform_inclusive_scan is that transform_inclusive_scan includes the ith
 * input element from the ith sum. If binary_op is not mathematically
 * associative, the behavior of transform_inclusive_scan may be nondeterministic.
 * transform_inclusive_scan does not apply unary_op to init.
 */
template<typename InputIterator, typename OutputIterator,
         typename UnaryOperation, typename BinaryOperation,
         utils::EnableIf<utils::isInputIt<InputIterator>> = nullptr>
OutputIterator
transform_inclusive_scan(InputIterator first, InputIterator last,
               OutputIterator result,
               UnaryOperation unary_op,
               BinaryOperation binary_op) {
  typedef typename std::iterator_traits<OutputIterator>::value_type Type;
  return transform_inclusive_scan(first, last, result, unary_op, binary_op, Type{});
}

/**
 * Effects: Assigns through each iterator i in [result,result + (last - first))
 * the value of GENERALIZED_NONCOMMUTATIVE_SUM(binary_op, unary_op(*first), ..., unary_op(*(first + (i - * result))))
 * or GENERALIZED_NONCOMMUTATIVE_SUM(binary_op, init, unary_op(*first), ..., unary_op(*(first + (i * - result)))) if init is provided.
 *
 * Return: The end of the resulting range beginning at result.
 *
 * Requires: Neither unary_op nor binary_op shall invalidate iterators or
 * subranges, or modify elements in the ranges [first,last) or
 * [result,result + (last - first)).
 *
 * Complexity: O(last - first) applications each of unary_op and binary_op.
 *
 * Notes: The difference between transform_exclusive_scan and
 * transform_inclusive_scan is that transform_inclusive_scan includes the ith
 * input element from the ith sum. If binary_op is not mathematically
 * associative, the behavior of transform_inclusive_scan may be nondeterministic.
 * transform_inclusive_scan does not apply unary_op to init.
 */
template<typename ExecutionPolicy,
         typename InputIterator, typename OutputIterator,
         typename UnaryOperation, typename BinaryOperation,
         utils::EnableIf<utils::isExecutionPolicy<ExecutionPolicy>> = nullptr,
         utils::EnableIf<utils::isInputIt<InputIterator>> = nullptr>
OutputIterator
transform_inclusive_scan(ExecutionPolicy&& exec,
                         InputIterator first, InputIterator last,
                         OutputIterator result,
                         UnaryOperation unary_op,
                         BinaryOperation binary_op) {
  if (utils::isParallel(exec)) {
    return transform_inclusive_scan(first, last, result, binary_op);
  } else {
    details::transform_impl(first, last, result, unary_op,
      std::input_iterator_tag{});
    const size_t N = static_cast<size_t>(std::distance(first, last));
    typedef typename std::iterator_traits<OutputIterator>::value_type Type;
    return details::inclusive_scan_impl(result, result + N, result, binary_op, Type{},
             std::input_iterator_tag{});
  }
}

