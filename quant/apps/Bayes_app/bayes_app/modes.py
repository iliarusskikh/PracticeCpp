"""Scenario mode definitions: labels, copy, and default probabilities."""

from __future__ import annotations

from dataclasses import dataclass

from bayes_app.models import ProbabilityInputs


@dataclass(frozen=True, slots=True)
class ModeDefinition:
    """A named teaching scenario that reuses the shared math/viz engine.

    Attributes:
        id: Stable key used by the UI selector.
        title: Short display title.
        description: Scenario framing shown above the controls.
        hypothesis_label: Human label for H (e.g. \"has disease\").
        evidence_label: Human label for E (e.g. \"positive test\").
        prior_label: Slider label for P(H).
        likelihood_label: Slider label for P(E|H).
        false_positive_label: Slider label for P(E|¬H).
        defaults: Default :class:`ProbabilityInputs`, or ``None`` for Custom.
        insight: Optional pedagogical callout after the posterior is shown.
    """

    id: str
    title: str
    description: str
    hypothesis_label: str
    evidence_label: str
    prior_label: str
    likelihood_label: str
    false_positive_label: str
    defaults: ProbabilityInputs | None
    insight: str


MEDICAL = ModeDefinition(
    id="medical",
    title="Medical Diagnostic Testing",
    description=(
        "A rare disease and an accurate-looking test. Prevalence is low, so even a "
        "strong positive result leaves substantial doubt — the classic base-rate lesson."
    ),
    hypothesis_label="Has the disease",
    evidence_label="Positive test",
    prior_label="Prevalence P(disease)",
    likelihood_label="Sensitivity P(+ | disease)",
    false_positive_label="False-positive rate P(+ | no disease)",
    defaults=ProbabilityInputs(prior=0.01, likelihood=0.99, false_positive=0.05),
    insight=(
        "With 1% prevalence, 99% sensitivity, and 5% FPR, most positive tests are "
        "false alarms. The posterior is far below what intuition expects from "
        '"99% accurate."'
    ),
)

TRADING = ModeDefinition(
    id="trading",
    title="Trading Signal / Backtest False-Discovery",
    description=(
        "Among many tested strategies, only a small fraction are genuinely predictive. "
        'A "significant" backtest still has a low positive predictive value when the '
        "base rate of true edges is small — base-rate neglect and p-hacking risk."
    ),
    hypothesis_label="Strategy is genuinely predictive",
    evidence_label="Passes significance test",
    prior_label="Base rate of true edges P(true)",
    likelihood_label="Power P(pass | true)",
    false_positive_label="Type I error P(pass | null)",
    defaults=ProbabilityInputs(prior=0.05, likelihood=0.90, false_positive=0.10),
    insight=(
        "If only 5% of ideas are real, 90% power and a 10% false-positive rate still "
        'imply that a large share of "significant" results are false discoveries.'
    ),
)

CUSTOM = ModeDefinition(
    id="custom",
    title="Custom",
    description=(
        "Define your own hypothesis H and evidence E. Sliders start at neutral 50% — "
        "set priors and likelihoods to match the question you care about."
    ),
    hypothesis_label="Hypothesis H",
    evidence_label="Evidence E",
    prior_label="Prior P(H)",
    likelihood_label="Likelihood P(E|H)",
    false_positive_label="False-positive rate P(E|¬H)",
    defaults=ProbabilityInputs(prior=0.5, likelihood=0.5, false_positive=0.5),
    insight=(
        "Posterior = likelihood × prior / evidence. Watch how a low prior dominates "
        "even a strong likelihood when false positives are non-trivial."
    ),
)

MODES: dict[str, ModeDefinition] = {
    MEDICAL.id: MEDICAL,
    TRADING.id: TRADING,
    CUSTOM.id: CUSTOM,
}


def get_mode(mode_id: str) -> ModeDefinition:
    """Return a mode by id.

    Args:
        mode_id: One of ``medical``, ``trading``, ``custom``.

    Returns:
        The matching :class:`ModeDefinition`.

    Raises:
        KeyError: If ``mode_id`` is unknown.
    """
    try:
        return MODES[mode_id]
    except KeyError as exc:
        raise KeyError(f"Unknown mode_id: {mode_id!r}") from exc
