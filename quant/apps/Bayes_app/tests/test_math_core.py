"""Unit tests for pure Bayes math (edge cases and invariants)."""

from __future__ import annotations

import math

import pytest
from bayes_app.math_core import (
    ProbabilityError,
    compute_bayes,
    marginal_evidence,
    natural_frequencies,
    posterior_given_evidence,
    sensitivity_curve,
)
from bayes_app.models import ProbabilityInputs
from bayes_app.modes import MEDICAL, TRADING, get_mode


class TestValidation:
    def test_rejects_negative(self) -> None:
        with pytest.raises(ProbabilityError, match="prior"):
            compute_bayes(-0.1, 0.5, 0.5)

    def test_rejects_above_one(self) -> None:
        with pytest.raises(ProbabilityError, match="likelihood"):
            compute_bayes(0.5, 1.1, 0.5)

    def test_rejects_nan(self) -> None:
        with pytest.raises(ProbabilityError, match="false_positive"):
            compute_bayes(0.5, 0.5, float("nan"))

    def test_rejects_inf(self) -> None:
        with pytest.raises(ProbabilityError):
            compute_bayes(float("inf"), 0.5, 0.5)

    def test_rejects_bool(self) -> None:
        with pytest.raises(ProbabilityError):
            compute_bayes(True, 0.5, 0.5)  # type: ignore[arg-type]

    def test_boundary_zero_and_one_accepted(self) -> None:
        result = compute_bayes(0.0, 1.0, 0.0)
        assert result.prior == 0.0
        assert result.likelihood == 1.0
        assert result.false_positive == 0.0


class TestBayesCore:
    def test_classic_medical_screening(self) -> None:
        """1% prevalence, 99% sensitivity, 5% FPR → posterior ≈ 16.67%."""
        assert MEDICAL.defaults is not None
        d = MEDICAL.defaults
        post = posterior_given_evidence(d.prior, d.likelihood, d.false_positive)
        assert post is not None
        # 0.99*0.01 / (0.99*0.01 + 0.05*0.99) = 0.0099 / 0.0594 ≈ 0.1667
        assert post == pytest.approx(0.1666666667, rel=1e-9)

    def test_trading_false_discovery(self) -> None:
        assert TRADING.defaults is not None
        d = TRADING.defaults
        post = posterior_given_evidence(d.prior, d.likelihood, d.false_positive)
        assert post is not None
        # 0.9*0.05 / (0.9*0.05 + 0.1*0.95) = 0.045 / 0.14 ≈ 0.3214
        assert post == pytest.approx(0.045 / 0.14, rel=1e-12)

    def test_prior_zero_gives_posterior_zero_when_evidence_possible(self) -> None:
        post = posterior_given_evidence(0.0, 0.9, 0.1)
        assert post == 0.0

    def test_prior_one_gives_posterior_one_when_evidence_possible(self) -> None:
        post = posterior_given_evidence(1.0, 0.9, 0.1)
        assert post == 1.0

    def test_perfect_test_recovers_certainty(self) -> None:
        """Zero FPR and likelihood 1 → posterior equals 1 for any prior > 0."""
        for prior in (0.01, 0.5, 0.99):
            post = posterior_given_evidence(prior, 1.0, 0.0)
            assert post == pytest.approx(1.0)

    def test_uninformative_evidence_leaves_prior(self) -> None:
        """When P(E|H) = P(E|¬H), posterior equals prior."""
        for prior in (0.1, 0.5, 0.8):
            rate = 0.3
            post = posterior_given_evidence(prior, rate, rate)
            assert post == pytest.approx(prior)

    def test_mutually_exclusive_evidence_undefined(self) -> None:
        """P(E|H)=P(E|¬H)=0 ⇒ P(E)=0 ⇒ posterior undefined."""
        result = compute_bayes(0.4, 0.0, 0.0)
        assert result.evidence == 0.0
        assert result.posterior is None
        assert result.posterior_complement is None
        assert not result.is_defined

    def test_evidence_impossible_with_prior_one_and_zero_likelihood(self) -> None:
        result = compute_bayes(1.0, 0.0, 0.5)
        assert result.evidence == 0.0
        assert result.posterior is None

    def test_marginal_evidence_bounds(self) -> None:
        e = marginal_evidence(0.2, 0.8, 0.1)
        assert 0.0 <= e <= 1.0
        assert e == pytest.approx(0.8 * 0.2 + 0.1 * 0.8)


class TestNaturalFrequencies:
    def test_counts_sum_to_n(self) -> None:
        counts = natural_frequencies(0.01, 0.99, 0.05, n=1000)
        total = counts.tp + counts.fn + counts.fp + counts.tn
        assert total == pytest.approx(1000.0)

    def test_medical_cell_expectations(self) -> None:
        counts = natural_frequencies(0.01, 0.99, 0.05, n=1000)
        assert counts.tp == pytest.approx(9.9)
        assert counts.fn == pytest.approx(0.1)
        assert counts.fp == pytest.approx(49.5)
        assert counts.tn == pytest.approx(940.5)

    def test_rejects_non_positive_n(self) -> None:
        with pytest.raises(ValueError, match="positive"):
            natural_frequencies(0.5, 0.5, 0.5, n=0)


class TestSensitivityCurve:
    def test_endpoints_and_length(self) -> None:
        curve = sensitivity_curve(0.9, 0.1, n_points=11)
        assert len(curve) == 11
        assert curve[0][0] == 0.0
        assert curve[-1][0] == 1.0
        assert curve[0][1] == 0.0
        assert curve[-1][1] == 1.0

    def test_undefined_when_both_rates_zero(self) -> None:
        curve = sensitivity_curve(0.0, 0.0, n_points=5)
        assert all(post is None for _, post in curve)

    def test_rejects_too_few_points(self) -> None:
        with pytest.raises(ValueError):
            sensitivity_curve(0.5, 0.5, n_points=1)


class TestModelsAndModes:
    def test_probability_inputs_roundtrip(self) -> None:
        inputs = ProbabilityInputs(prior=0.01, likelihood=0.99, false_positive=0.05)
        result = inputs.to_result()
        assert result.posterior == pytest.approx(1.0 / 6.0)

    def test_get_mode_unknown(self) -> None:
        with pytest.raises(KeyError):
            get_mode("nope")

    def test_posterior_finite_for_defaults(self) -> None:
        for mode_id in ("medical", "trading", "custom"):
            mode = get_mode(mode_id)
            assert mode.defaults is not None
            post = mode.defaults.to_result().posterior
            assert post is not None
            assert math.isfinite(post)
