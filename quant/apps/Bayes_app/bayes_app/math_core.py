"""Pure Bayes' theorem calculations with no UI dependencies."""

from __future__ import annotations

from dataclasses import dataclass


class ProbabilityError(ValueError):
    """Raised when a probability input is outside [0, 1] or otherwise invalid."""


def _validate_probability(name: str, value: float) -> float:
    """Validate that ``value`` is a finite probability in [0, 1].

    Args:
        name: Parameter name used in error messages.
        value: Candidate probability.

    Returns:
        The validated float.

    Raises:
        ProbabilityError: If ``value`` is not a finite number in [0, 1].
    """
    if not isinstance(value, (int, float)) or isinstance(value, bool):
        raise ProbabilityError(f"{name} must be a real number, got {type(value).__name__}")
    value_f = float(value)
    if value_f != value_f:  # NaN
        raise ProbabilityError(f"{name} must be finite, got NaN")
    if value_f in (float("inf"), float("-inf")):
        raise ProbabilityError(f"{name} must be finite, got {value_f}")
    if not 0.0 <= value_f <= 1.0:
        raise ProbabilityError(f"{name} must be in [0, 1], got {value_f}")
    return value_f


@dataclass(frozen=True, slots=True)
class BayesInputs:
    """Inputs to Bayes' theorem for a binary hypothesis and evidence.

    Attributes:
        prior: P(H), prior probability of the hypothesis.
        likelihood: P(E|H), true-positive rate / sensitivity / power.
        false_positive: P(E|¬H), false-positive rate / Type I error.
    """

    prior: float
    likelihood: float
    false_positive: float

    def __post_init__(self) -> None:
        object.__setattr__(self, "prior", _validate_probability("prior", self.prior))
        object.__setattr__(self, "likelihood", _validate_probability("likelihood", self.likelihood))
        object.__setattr__(
            self,
            "false_positive",
            _validate_probability("false_positive", self.false_positive),
        )

    @property
    def prior_complement(self) -> float:
        """P(¬H) = 1 − P(H)."""
        return 1.0 - self.prior


@dataclass(frozen=True, slots=True)
class BayesResult:
    """Computed quantities from Bayes' theorem.

    Attributes:
        prior: P(H).
        likelihood: P(E|H).
        false_positive: P(E|¬H).
        evidence: P(E), marginal probability of observing the evidence.
        posterior: P(H|E), or ``None`` when P(E) = 0 (undefined).
        posterior_complement: P(¬H|E), or ``None`` when undefined.
    """

    prior: float
    likelihood: float
    false_positive: float
    evidence: float
    posterior: float | None
    posterior_complement: float | None

    @property
    def is_defined(self) -> bool:
        """Whether the posterior is mathematically defined."""
        return self.posterior is not None


@dataclass(frozen=True, slots=True)
class ContingencyCounts:
    """Natural-frequency / confusion-matrix cell counts for a population of size N.

    Cells follow the usual diagnostic naming:
        TP = H ∧ E, FN = H ∧ ¬E, FP = ¬H ∧ E, TN = ¬H ∧ ¬E.
    """

    n: int
    tp: float
    fn: float
    fp: float
    tn: float

    @property
    def with_hypothesis(self) -> float:
        """Expected count with H true (TP + FN)."""
        return self.tp + self.fn

    @property
    def without_hypothesis(self) -> float:
        """Expected count with H false (FP + TN)."""
        return self.fp + self.tn

    @property
    def with_evidence(self) -> float:
        """Expected count with E observed (TP + FP)."""
        return self.tp + self.fp

    @property
    def without_evidence(self) -> float:
        """Expected count with E absent (FN + TN)."""
        return self.fn + self.tn


def marginal_evidence(prior: float, likelihood: float, false_positive: float) -> float:
    """Compute the marginal probability of evidence P(E).

    .. math::

        P(E) = P(E|H) P(H) + P(E|¬H) P(¬H)

    Args:
        prior: P(H).
        likelihood: P(E|H).
        false_positive: P(E|¬H).

    Returns:
        P(E) in [0, 1].

    Raises:
        ProbabilityError: If any input is outside [0, 1].
    """
    inputs = BayesInputs(prior=prior, likelihood=likelihood, false_positive=false_positive)
    return inputs.likelihood * inputs.prior + inputs.false_positive * inputs.prior_complement


def posterior_given_evidence(
    prior: float, likelihood: float, false_positive: float
) -> float | None:
    """Compute the posterior P(H|E).

    .. math::

        P(H|E) = \\frac{P(E|H) P(H)}{P(E)}

    When P(E) = 0 the posterior is undefined and ``None`` is returned (e.g. both
    likelihood and false-positive rate are zero — mutually exclusive with observing E).

    Args:
        prior: P(H).
        likelihood: P(E|H).
        false_positive: P(E|¬H).

    Returns:
        P(H|E) in [0, 1], or ``None`` if undefined.

    Raises:
        ProbabilityError: If any input is outside [0, 1].
    """
    inputs = BayesInputs(prior=prior, likelihood=likelihood, false_positive=false_positive)
    evidence = marginal_evidence(inputs.prior, inputs.likelihood, inputs.false_positive)
    if evidence == 0.0:
        return None
    return (inputs.likelihood * inputs.prior) / evidence


def compute_bayes(prior: float, likelihood: float, false_positive: float) -> BayesResult:
    """Compute a full Bayes result bundle from the three core inputs.

    Args:
        prior: P(H).
        likelihood: P(E|H).
        false_positive: P(E|¬H).

    Returns:
        A :class:`BayesResult` with marginal evidence and posterior (if defined).

    Raises:
        ProbabilityError: If any input is outside [0, 1].
    """
    inputs = BayesInputs(prior=prior, likelihood=likelihood, false_positive=false_positive)
    evidence = marginal_evidence(inputs.prior, inputs.likelihood, inputs.false_positive)
    posterior = posterior_given_evidence(inputs.prior, inputs.likelihood, inputs.false_positive)
    posterior_complement = None if posterior is None else 1.0 - posterior
    return BayesResult(
        prior=inputs.prior,
        likelihood=inputs.likelihood,
        false_positive=inputs.false_positive,
        evidence=evidence,
        posterior=posterior,
        posterior_complement=posterior_complement,
    )


def natural_frequencies(
    prior: float,
    likelihood: float,
    false_positive: float,
    *,
    n: int = 1000,
) -> ContingencyCounts:
    """Translate probabilities into expected natural-frequency cell counts.

    Args:
        prior: P(H).
        likelihood: P(E|H).
        false_positive: P(E|¬H).
        n: Reference population size (must be positive).

    Returns:
        Expected TP / FN / FP / TN counts that sum to ``n``.

    Raises:
        ProbabilityError: If any probability is invalid.
        ValueError: If ``n`` is not a positive integer.
    """
    if not isinstance(n, int) or isinstance(n, bool) or n <= 0:
        raise ValueError(f"n must be a positive integer, got {n!r}")
    inputs = BayesInputs(prior=prior, likelihood=likelihood, false_positive=false_positive)
    p_h = inputs.prior
    p_not_h = inputs.prior_complement
    tp = n * p_h * inputs.likelihood
    fn = n * p_h * (1.0 - inputs.likelihood)
    fp = n * p_not_h * inputs.false_positive
    tn = n * p_not_h * (1.0 - inputs.false_positive)
    return ContingencyCounts(n=n, tp=tp, fn=fn, fp=fp, tn=tn)


def sensitivity_curve(
    likelihood: float,
    false_positive: float,
    *,
    n_points: int = 201,
) -> list[tuple[float, float | None]]:
    """Evaluate P(H|E) across a dense grid of prior values.

    Args:
        likelihood: P(E|H), held fixed.
        false_positive: P(E|¬H), held fixed.
        n_points: Number of prior samples in [0, 1] (inclusive).

    Returns:
        List of ``(prior, posterior)`` pairs. Posterior is ``None`` where undefined.

    Raises:
        ProbabilityError: If likelihood / false-positive are invalid.
        ValueError: If ``n_points`` < 2.
    """
    if n_points < 2:
        raise ValueError(f"n_points must be >= 2, got {n_points}")
    _validate_probability("likelihood", likelihood)
    _validate_probability("false_positive", false_positive)
    step = 1.0 / (n_points - 1)
    points: list[tuple[float, float | None]] = []
    for i in range(n_points):
        prior = i * step
        # Clamp final point to exactly 1.0 to avoid float drift.
        if i == n_points - 1:
            prior = 1.0
        points.append((prior, posterior_given_evidence(prior, likelihood, false_positive)))
    return points
